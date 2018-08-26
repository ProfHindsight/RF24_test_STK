/*
 * HardwareSPI.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Colton
 */

#include "HardwareSPI.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"



HardwareSPI::HardwareSPI()
{
	CMU_ClockEnable(cmuClock_GPIO, true);
	// This stuff should be defined elsewhere. Otherwise we can't use two different NRF chips.
	CMU_ClockEnable(cmuClock_USART1, true);
	/*
		MOSI PD0
		MISO PD1
		SCK PD2
		CSN PD3
		CE PD4
		IRQ PD5
		*/
		GPIO_PinModeSet(gpioPortD, 					0, 						gpioModePushPull, 	1	);		// Tx
		GPIO_PinModeSet(gpioPortD, 					1, 						gpioModeInput	, 	0	);		// Rx
		GPIO_PinModeSet(gpioPortD, 					2, 						gpioModePushPull, 	1	);		// Clock
		GPIO_PinModeSet(gpioPortD, 					5, 						gpioModeInput	,	0	);		// IRQ
		GPIO_PinModeSet(gpioPortD, 					4, 						gpioModePushPull, 	1	);		// Chip Enable
		GPIO_PinModeSet(gpioPortD, 					3, 						gpioModePushPull, 	1	);		// Chip Select

		USART_InitSync_TypeDef init = {
										usartEnable,       /* Enable RX/TX when init completed. */
										0,                 /* Use current configured reference clock for configuring baudrate. */
										1000000,           /* 1 Mbits/s. */
										usartDatabits8,    /* 8 databits. */
										true,              /* Master mode. */
										true,              /* Send most significant bit first. */
										usartClockMode0,   /* Clock idle low, sample on rising edge. */
										false,             /* Not USART PRS input mode. */
										usartPrsRxCh0,     /* PRS channel 0. */
										false};            /* No AUTOTX mode. */

		USART_InitSync(USART1, &init);

	    USART1->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN |
	                USART_ROUTE_CLKPEN | USART_ROUTE_LOCATION_LOC1;
}

HardwareSPI::~HardwareSPI() 
{
	// TODO Auto-generated destructor stub
}

uint8_t HardwareSPI::transfer(uint8_t data) 
{
	return USART_SpiTransfer(USART1, data);
}

void HardwareSPI::transfer(uint8_t* buffer, uint32_t size)
{
	uint32_t i = 0;
	while(i < size)
	{
		USART_Tx(USART1, buffer[i++]);
	}
}
