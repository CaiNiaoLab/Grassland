/*
 * i2cdev.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月3日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */
#include <i2cdev.h>

static bool g_IsInitialized = false;
extern const I2C_Config I2C_config[];
extern const uint_least8_t g_I2CCount;

void I2C_Device_Init(void) {
	uint_fast8_t i;

	if (!g_IsInitialized) {
		g_IsInitialized = (bool) true;

		for (i = 0; i < g_I2CCount; i++) {
			I2C_config[i].fxnTablePtr->initFxn((I2C_Handle) &(I2C_config[i]));
		}
	}
}

bool I2C_Device_Transfer(uint_least8_t index, I2C_Transaction *transaction) {
	I2C_Handle handle = NULL;
	int_fast16_t result;
	if (g_IsInitialized && (index < g_I2CCount)) {
		handle = (I2C_Handle) &(I2C_config[index]);
	}

	result = handle->fxnTablePtr->transferFxn(handle, transaction,
	I2C_WAIT_FOREVER);
	if (result == I2C_STATUS_SUCCESS) {
		return (true);
	} else {
		return (false);
	}
}

I2C_Handle I2C_Device_Close(uint_least8_t index) {
	I2C_Handle handle = NULL;
	return (handle);
}
