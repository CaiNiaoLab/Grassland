/*
 * gpiodev.h
 *
 *  Created on: 2021Äê4ÔÂ29ÈÕ
 *      Author: DELL
 */

#ifndef GPIODEV_H_
#define GPIODEV_H_

#include <gpiodrv.h>

void GPIO_Device_Init(void);
GPIO_Handle GPIO_Device_Open(uint_least8_t index);
GPIO_Handle GPIO_Device_Close(uint_least8_t index);
#endif /* GPIODEV_H_ */
