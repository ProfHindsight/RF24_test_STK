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

#define MS_TO_SLEEP				60000

I2C_TypeDef* i2c;
RTCDRV_TimerID_t rtc_id;
minimalist_packet data;
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
	  bmp280_read_pressure_temperature(&data.BMP280_pres, &data.BMP280_temp);
	  bmp280_set_power_mode(0x01);
	  print("BMP280 Temp: %d\nBMP280 pres: %d\n", data.BMP280_temp, data.BMP280_pres);
	}


	/**
	* Read temperature and humidity, and start another conversion
	*/
	if(si_available)
	{
	  Si7013_MeasureRHAndTemp(i2c, Si7020_device_address, &data.Si7020_humid, &data.Si7020_temp);
	  print("Si7020 Temp: %d\nSi7020 RH: %d\n", data.Si7020_temp, data.Si7020_humid);
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
	i2c = I2C0;

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
	RTCDRV_StartTimer(
		  rtc_id, 						// RTC ID
		  rtcdrvTimerTypePeriodic, 		// Type
		  MS_TO_SLEEP, 					// Amount (milliseconds)
		  NULL, 						// Callback Function
		  NULL);						// Garbage User Data


#if defined (HARDWARE_VERSION_2_0)
	data.VBUS_available = GPIO_PinInGet(gpioPortB, 14);
	data.hardware_revision[0] = '2';
	data.hardware_revision[1] = '0';

#elif defined (HARDWARE_VERSION_1_0)
	data.VBUS_available = 0;
	data.hardware_revision[0] = '1';
	data.hardware_revision[1] = '0';
#else
	data.VBUS_available = 0;
	data.hardware_revision[0] = '0';
	data.hardware_revision[1] = '0';
#endif
	data.unique_id_0 =  *(uint32_t*)0xFE081F0;
	data.unique_id_1 =  *(uint32_t*)0xFE081F4;
	data.packet_type = minimalist_packet_type;
	data.bmp280_available = bmp_available;
	data.si7020_available = si_available;

	/* Infinite loop */
	while (1) {

		// Read the sensors
		read_sensors();
#if defined (HARDWARE_VERSION_2_0)
	data.VBUS_available = GPIO_PinInGet(gpioPortB, 14);
#endif

		// Transmit the data
		transmit_packet(&data, minimalist_packet_size);

		prepare_sleep();
		SLEEP_Sleep();
		prepare_wakeup();
	}
}
