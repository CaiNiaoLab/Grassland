/*
 * gpiodev.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年4月29日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */
#include <gpiodev.h>
#include <stdio.h>
#include <stdbool.h>

static bool g_IsInitialized = false;
extern const GPIO_Config GPIO_config[];
extern const uint_least8_t g_GPIOCount;

void GPIO_Device_Init(void) {
	uint_fast8_t i;

	if (!g_IsInitialized) {
		g_IsInitialized = (bool) true;

		for (i = 0; i < g_GPIOCount; i++) {
			GPIO_config[i].fxnTablePtr->initFxn(
					(GPIO_Handle) &(GPIO_config[i]));
		}
	}
}

GPIO_Handle GPIO_Device_Open(uint_least8_t index) {
	GPIO_Handle handle = NULL;
	if (g_IsInitialized && (index < g_GPIOCount)) {
		handle = (GPIO_Handle) &(GPIO_config[index]);
		handle = handle->fxnTablePtr->openFxn(handle);
	}
	return (handle);
}

GPIO_Handle GPIO_Device_Close(uint_least8_t index) {
	GPIO_Handle handle = NULL;
	if (g_IsInitialized && (index < g_GPIOCount)) {
		handle = (GPIO_Handle) &(GPIO_config[index]);
		handle = handle->fxnTablePtr->closeFxn(handle);
	}
	return (handle);
}
