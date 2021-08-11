/*
 * main.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月10日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <gpiodev.h>
#include <i2cdev.h>

#include "dyBoardInit.h"


int main(void) {
	CC3200BoardInit();
	I2C_Transaction transaction;
	unsigned short usManufacID;
	uint8_t writedata = 0xff;

	transaction.slavAddress = 0x41;
    transaction.writeBuf = &writedata;
    transaction.readBuf = &writedata;
    transaction.writeCount = 1;
    transaction.readCount = 2;

	GPIO_Device_Init();
	I2C_Device_Init();
	while(1) {
	    GPIO_Device_Open(kREDLED);
	    MAP_UtilsDelay(8000000);
	    GPIO_Device_Close(kREDLED);
	    MAP_UtilsDelay(8000000);
	    I2C_Device_Open(kTMP006, &transaction);
	    usManufacID = (unsigned short) (transaction.readBuf[0] << 8) | transaction.readBuf[1];
	    printf("Manufacturer ID: 0x%04x\n\r", usManufacID);
	    writedata = 0xff;
	}
}
