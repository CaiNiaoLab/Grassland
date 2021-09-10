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
#include "sensor_management.h"

/*
 * 用于测试文件
 */
int main_test(void) {
	float fAmbient, fObject;
	int_fast32_t i32IntegerPart;
	int_fast32_t i32FractionPart;
	float Data[2] = {0};
	float *DataAddr = &Data[0];

	CC3200BoardInit();
	GPIO_Device_Init();
	I2C_Device_Init();
	Sensor_Init();

	while (1) {
		GPIO_Device_Open(kREDLED);
		MAP_UtilsDelay(8000000);
		GPIO_Device_Close(kREDLED);
		MAP_UtilsDelay(8000000);

		Sensor_Read_Float(kTMP006,DataAddr);

		fAmbient = Data[0];
		i32IntegerPart = (int32_t) fAmbient;
		i32FractionPart = (int32_t) (fAmbient * 1000.0f);
		i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
		if (i32FractionPart < 0) {
			i32FractionPart *= -1;
		}
		printf("Ambient %3d.%03d\t", i32IntegerPart, i32FractionPart);

		//< Convert the floating point ambient temperature  to an integer part
		//< and fraction part for easy printing.
		fObject = Data[1];
		i32IntegerPart = (int32_t) fObject;
		i32FractionPart = (int32_t) (fObject * 1000.0f);
		i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
		if (i32FractionPart < 0) {
			i32FractionPart *= -1;
		}
		printf("Object %3d.%03d\n", i32IntegerPart, i32FractionPart);
	}
}
