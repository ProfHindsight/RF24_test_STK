/*
 * utilities.cpp
 *
 *  Created on: Jul 12, 2018
 *      Author: Colton
 */

#include "em_usart.h"
#include "ustimer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include "RF24.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"

#define DEBUG

HardwareSPI _SPI;

volatile uint32_t msTicks;

#if defined(CUSTOM_BOARD)
RF24 radio(gpioPortA, 0, gpioPortB, 8);
#else
RF24 radio(gpioPortD, 4, gpioPortD, 3);
#endif
const uint32_t gateway_address 	= {		0xdf569390};
const uint32_t default_node_address = {	0xac04b1a4};

void prepareRF24(void)
{
	radio.setChannel(1);
//	radio.setPayloadSize(18);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_1MBPS);
	radio.setAutoAck(1);                     // Ensure autoACK is enabled
	radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
	radio.setAddressWidth(4);
	radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
	radio.stopListening();
	radio.openWritingPipe(gateway_address);
	radio.openReadingPipe(1,default_node_address);

	println("Started Listening!");
	radio.startListening();                 // Start listening
	radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}
void prepare_uart(void)
{
#if defined( DEBUG )
	USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
	init.baudrate = 115200;
	init.enable = usartEnable;
	USART_InitAsync(UART0, &init);
	USART_Enable(UART0, usartEnable);
	UART0->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC1;
#endif
}
void prepareClocks(void)
{
	// Enable common clocks
	CMU_ClockDivSet(cmuClock_HF, cmuClkDiv_2);
	CMU_OscillatorEnable(cmuOsc_HFXO, true, true);
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
#if defined (DEBUG )
	CMU_ClockEnable(cmuClock_UART0, true);
#endif
	CMU_ClockEnable(cmuClock_GPIO, true);
	// Start the ms ticks counter
		if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000))
		  while(1);
}

void prepareGPIO(void)
{

	GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 0);
	UART0->ROUTE = UART_ROUTE_LOCATION_LOC1 | UART_ROUTE_RXPEN | UART_ROUTE_TXPEN;
}

void delayMicroseconds(uint32_t microseconds)
{
	USTIMER_DelayIntSafe(microseconds);
}

uint8_t min(uint8_t a, uint8_t b)
{
	if(a < b) return a;
	else return b;
}


uint32_t millis(void)
{
	return msTicks;
}

void SysTick_Handler(void)
{
	msTicks++;
}

void delay(uint32_t milliseconds)
{
	uint32_t start = msTicks;
	while ((msTicks - start) < milliseconds);
}

void send_string(char * string)
{
      while (*string != 0)
      {
            if (*string == '\n')
            {
                  USART_Tx(UART0, '\r');
            }
            USART_Tx(UART0, *string++);
      }
}


void print(const char* format, ...)
{
#if defined(DEBUG)

    char       msg[130];
    va_list    args;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args); // do check return value
    va_end(args);

    send_string(msg);

#endif
}

void println(const char* format, ...)
{
#if defined(DEBUG)

    char       msg[130];
    va_list    args;

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args); // do check return value
    va_end(args);

    send_string(msg);

    char terminator[5] =  "\n\r";
    send_string(terminator);

#endif
}

void print(unsigned long int input)
{
#if defined(DEBUG)
	print("%i", input);
#endif
}

void println(unsigned long int input)
{
#if defined(DEBUG)
	println("%i", input);
#endif
}

uint8_t uart_rx(void)
{
	return USART_Rx(UART0);
}

bool uart_available(void)
{
	return ((USART_StatusGet(UART0) & USART_STATUS_RXDATAV));
}

uint8_t hex_to_decimal(uint8_t input)
{
	int i = 0;
	char str[] = "0123456789abcdef";
	while(input != str[i]) i++;
	return i;
}

void prepare_sleep(void)
{
	print("Going to sleep\n");
#if defined(DEBUG)
	//Wait for the LEUART to clear out
	while(USART_StatusGet(UART0) & (1 << 3));
	delay(2);
#endif
}

void prepare_wakeup(void)
{
	radio.powerUpNoWait();
}

bool transmit_packet(void* buf, uint8_t len)
{
	uint8_t* current = reinterpret_cast<uint8_t*>(buf);
	for(int i = 0; i < len; i++)
	{
		uint8_t chartosend = current[i];
		USART_Tx(UART0, chartosend);
	}
	while(!radio.isPowerUpReady());
	radio.stopListening();
	bool success =  radio.write(buf, len);
	radio.startListening();
	println("");
	return success;
}

bool receive_packet(void* buf, uint8_t len)
{
	while(!radio.isPowerUpReady());
	uint32_t startTicks = msTicks;
	while((msTicks - startTicks) < 500)
	{
		if(radio.available())
		{
			radio.read(buf, len);
			return true;
		}
	}
	return false;
}

void reconfigure_radio(provision_packet* input)
{
	radio.stopListening();
	radio.openWritingPipe(input->address);
	radio.startListening();
}
