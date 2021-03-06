/*
 * i2cdev.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月3日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */
#ifndef I2CDEV_H_
#define I2CDEV_H_

#include <i2cdrv.h>

#ifdef __cplusplus
extern "C" {
#endif

void I2C_Device_Init(void);
bool I2C_Device_Transfer(uint_least8_t index, I2C_Transaction *transaction);
I2C_Handle I2C_Device_Close(uint_least8_t index);

#ifdef __cplusplus
}
#endif

#endif /* I2CDEV_H_ */
