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
#include "tmp006.h"

/*
 * 用于测试文件
 */
int main(void) {
	float fAmbient, fObject;
	int_fast32_t i32IntegerPart;
	int_fast32_t i32FractionPart;
	TMP006 *g_sTMP006Inst = TMP006_new();

	CC3200BoardInit();
	GPIO_Device_Init();
	I2C_Device_Init();

	g_sTMP006Inst->Init(g_sTMP006Inst, kTMP006, kADDRPIN_ADR0);

	while (1) {
		GPIO_Device_Open(kREDLED);
		MAP_UtilsDelay(8000000);
		GPIO_Device_Close(kREDLED);
		MAP_UtilsDelay(8000000);

		g_sTMP006Inst->DataRead(g_sTMP006Inst);
		g_sTMP006Inst->DataTemperatureGetFloat(g_sTMP006Inst, &fAmbient, \
				&fObject);
		i32IntegerPart = (int32_t) fAmbient;
		i32FractionPart = (int32_t) (fAmbient * 1000.0f);
		i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
		if (i32FractionPart < 0) {
			i32FractionPart *= -1;
		}
		printf("Ambient %3d.%03d\t", i32IntegerPart, i32FractionPart);

		//< Convert the floating point ambient temperature  to an integer part
		//< and fraction part for easy printing.
		i32IntegerPart = (int32_t) fObject;
		i32FractionPart = (int32_t) (fObject * 1000.0f);
		i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
		if (i32FractionPart < 0) {
			i32FractionPart *= -1;
		}
		printf("Object %3d.%03d\n", i32IntegerPart, i32FractionPart);
	}
}
