#include "em_device.h"
#include "em_core.h"
#include "si7013.h"
#include "i2cspmconfig.h"
#include "i2cspm.h"
#include "sleep.h"
#include "rtcdriver.h"
#include "RF24.h"
#include "BMP280.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_chip.h"
#include <stdio.h>
#include <stdarg.h>
#include "utilities.h"
#include "ustimer.h"
#include "ecode.h"
#include "em_gpio.h"
#include "em_usart.h"

// For some reason, the device address needs to include the R/W bit. Strange.
#define Si7020_device_address 	0x80
#define BMP280_device_address	0xEE

#define MS_DELAY_BETWEEN_PACKETS	5000

I2C_TypeDef* i2c;
RTCDRV_TimerID_t rtc_id;
provision_packet node_provision_packet;
node_data_packet node_data;
bool bmp_available = false;
bool si_available = false;

int8_t BMP280_I2C_read(u8 device_addr, u8 register_addr, u8 * data, u8 length)
{
	I2C_TransferSeq_TypeDef seq;

	// Define the device address
	seq.addr = device_addr;

	// We need to write to the register and read, i think
	seq.flags = I2C_FLAG_WRITE_READ;

	// Place the address into the first buffer
	seq.buf[0].data = &register_addr;
	seq.buf[0].len = 1;

	// Setup the read function
	seq.buf[1].data = data;
	seq.buf[1].len = length;

	return I2CSPM_Transfer(i2c, &seq);
}

// This one is similar, but a little different. Here we use the write write to write the address first.
int8_t BMP280_I2C_write(u8 device_addr, u8 register_addr, u8 * data, u8 length)
{
	I2C_TransferSeq_TypeDef seq;

	// Define the device address
	seq.addr = device_addr;

	// We need to write to the register and read, i think
	seq.flags = I2C_FLAG_WRITE_WRITE;

	// Place the address into the first buffer
	seq.buf[0].data = &register_addr;
	seq.buf[0].len = 1;

	// Setup the read function
	seq.buf[1].data = data;
	seq.buf[1].len = length;

	return I2CSPM_Transfer(i2c, &seq);
}

void read_sensors(void)
{
	/**
	* Read pressure and temperature, and start another conversion
	*/
	if(bmp_available)
	{
	  bmp280_read_pressure_temperature(&node_data.BMP280_pres, &node_data.BMP280_temp);
	  bmp280_set_power_mode(0x01);
	  print("BMP280 Temp: %d\nBMP280 pres: %d\n", node_data.BMP280_temp, node_data.BMP280_pres);
	}


	/**
	* Read temperature and humidity, and start another conversion
	*/
	if(si_available)
	{
	  Si7013_MeasureRHAndTemp(i2c, Si7020_device_address, &node_data.Si7020_humid, &node_data.Si7020_temp);
	  print("Si7020 Temp: %d\nSi7020 RH: %d\n", node_data.Si7020_temp, node_data.Si7020_humid);
	}
}

int main(void)
{

	/* Chip errata */
	CHIP_Init();

	prepareClocks();
	prepareGPIO();
	USTIMER_Init();

	// LEUART init

	prepare_uart();

	println("Hello");

	prepareRF24();

	// I2C init
	I2CSPM_Init_TypeDef i2cspm_init_struct = I2CSPM_INIT_DEFAULT;
	I2CSPM_Init(&i2cspm_init_struct);
	i2c = i2cspm_init_struct.port;

	SLEEP_Init(NULL, NULL);
	SLEEP_SleepBlockBegin(sleepEM3); // EM3 and EM4 are blocked

	RTCDRV_Init();
	RTCDRV_AllocateTimer(&rtc_id);

	struct bmp280_t bmp280initstruct;
	bmp280initstruct.bus_read 	= BMP280_I2C_read;
	bmp280initstruct.bus_write 	= BMP280_I2C_write;
	bmp280initstruct.delay_msec 	= delay;
	bmp280initstruct.dev_addr 	= BMP280_device_address;
	if(bmp280_init(&bmp280initstruct) == 0) bmp_available = true;

	if(bmp_available) 	print("BMP280 Found!\n");
	else 				print("BMP280 Not Found!\n");

	if(bmp_available)
	{
		bmp280_set_oversamp_temperature(0x00);
		bmp280_set_filter(0x00);
		bmp280_set_power_mode(0x01);
		bmp280_set_work_mode(0x00);
	}


	uint8_t Si7020_id;
	if(Si7013_Detect(i2c, Si7020_device_address, &Si7020_id) == 1)
			si_available = true;

	if(si_available) print("Si7020 Found!\n");
	else print("Si7020 Not Found!\n");

	/**
	* Transmit data to the gateway about what's here.
	*/
	bool connected = false;
	RTCDRV_StartTimer(
		  rtc_id, 						// RTC ID
		  rtcdrvTimerTypePeriodic, 		// Type
		  10000, 						// Amount (milliseconds)
		  NULL, 						// Callback Function
		  NULL);						// Garbage User Data

	discover_packet discover;
	discover.packet_type = discover_packet_type;
	char temp_msg[] = "I'm here!\n\0";
	for(uint8_t i = 0; i < (sizeof(temp_msg)/sizeof(char)); i++)
	{
	  discover.message[i] = temp_msg[i];
	}
	uint32_t lastMsTicks = millis();
	while(!connected)
	{
		if(millis() - lastMsTicks > 1)
		{
			SLEEP_Sleep();
			lastMsTicks = millis();
		}
		transmit_packet(&discover, discover_packet_size);
		if(receive_packet(&discover, discover_packet_size))
		{
			char password[] = "I hear you";
			uint8_t i = 0;
			for(i = 0; i < (sizeof(password) / sizeof(char)); i++)
			{
				if(!(discover.message[i] == password[i]))
					i = 100;
			}
			if(i != 100)
			{
				receive_packet(&node_provision_packet, provision_packet_size);
				reconfigure_radio(&node_provision_packet);
				lastMsTicks = millis();
				node_info_packet buf;
				buf.packet_type = node_info_packet_type;
				if(si_available) buf.si7020_available = 1;
				else buf.si7020_available = 0;
				if(bmp_available) buf.bmp280_available = 1;
				else buf.bmp280_available = 0;
				delay(5);
#if defined (HARDWARE_VERSION_2_0)
				buf.VBUS_available = GPIO_PinInGet(gpioPortB, 14);
				buf.hardware_revision[0] = '2';
				buf.hardware_revision[1] = '0';

#elif defined (HARDWARE_VERSION_1_0)
				buf.VBUS_available = 0;
				buf.hardware_revision[0] = '1';
				buf.hardware_revision[1] = '0';
#else
				buf.VBUS_available = 0;
				buf.hardware_revision[0] = '0';
				buf.hardware_revision[1] = '0';
#endif
				transmit_packet(&buf, node_info_packet_size);
				RTCDRV_StopTimer(rtc_id);
				RTCDRV_StartTimer(
							  rtc_id, 						// RTC ID
							  rtcdrvTimerTypePeriodic, 		// Type
							  node_provision_packet.mswait,	// Amount (milliseconds)
							  NULL, 						// Callback Function
							  NULL);						// Garbage User Data
				SLEEP_Sleep();
				connected = true;
			}

		}
	}

	gateway_ack_packet ack;
	ack.packet_type = gateway_ack_packet_type;
	ack.msWait = MS_DELAY_BETWEEN_PACKETS;
	uint8_t failures = 0;
	node_data.packet_type = node_data_packet_type;
	/* Infinite loop */
	while (1) {

		// Read the sensors
		read_sensors();

		// Transmit the data
		transmit_packet(&node_data, node_data_packet_size);

		// Attempt to receive a packet
		if(!receive_packet(&ack, gateway_ack_packet_size))
		{
			failures++;
		}
		else
		{
			failures = 0;
		}

		// If we failed x times in a row, invoke a SW reset.
		if(failures == 8)
		{
			NVIC_SystemReset();
		}

		// Start the timer again
		RTCDRV_StartTimer(
				  rtc_id, 						// RTC ID
				  rtcdrvTimerTypeOneshot, 		// Type
				  ack.msWait,					// Amount (milliseconds)
				  NULL, 						// Callback Function
				  NULL);						// Garbage User Data
		prepare_sleep();
		SLEEP_Sleep();
		prepare_wakeup();
	}
}
