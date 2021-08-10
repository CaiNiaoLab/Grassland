/*
 * gpiodev.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年4月29日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef GPIODEV_H_
#define GPIODEV_H_

#include <gpiodrv.h>

void GPIO_Device_Init(void);
GPIO_Handle GPIO_Device_Open(uint_least8_t index);
GPIO_Handle GPIO_Device_Close(uint_least8_t index);
#endif /* GPIODEV_H_ */
