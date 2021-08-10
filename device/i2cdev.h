/*
 * i2cdev.h
 *
 *  Created on: 2021Äê8ÔÂ3ÈÕ
 *      Author: DELL
 */

#ifndef I2CDEV_H_
#define I2CDEV_H_

#include <i2cdrv.h>

void I2C_Device_Init(void);
bool I2C_Device_Open(uint_least8_t index, I2C_Transaction *transaction);
I2C_Handle I2C_Device_Close(uint_least8_t index);


#endif /* I2CDEV_H_ */
