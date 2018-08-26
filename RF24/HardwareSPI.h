/*
 * HardwareSPI.h
 *
 *  Created on: Apr 21, 2018
 *      Author: Colton
 */

#ifndef SRC_HARDWARESPI_H_
#define SRC_HARDWARESPI_H_


#include "em_usart.h"
#include "em_gpio.h"
#include "em_cmu.h"


class HardwareSPI {
public:
	HardwareSPI();
	virtual ~HardwareSPI();
	uint8_t transfer(uint8_t);
	void transfer(uint8_t*, uint32_t);
};

#endif /* SRC_HARDWARESPI_H_ */
