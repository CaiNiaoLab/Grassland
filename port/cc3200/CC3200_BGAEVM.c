/*
 * CC3200MSP432E411Y_BGAEVM.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月1日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <gpiodrv.h>

#include <stdio.h>

#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"

/*
 *  =============================== GPIO ===============================
 */
GPIO_Object gpioCC3200Objects[kMCU_COUNT] = {
	{
		.dircetion = GPIO_DIR_MODE_OUT,
		.pin_mode = PIN_MODE_0,
		.pin_address = 0x02,
	}
};

const GPIOMCU_HWAttrs gpioCC3200HWAttrs[kMCU_COUNT] = {
	{
		.base_port =GPIOA1_BASE,
		.pin_num = 9,
		.init_pin = PIN_64,
	}
};

const GPIO_Config GPIO_config[kMCU_COUNT] = {
	{
		.fxnTablePtr =&GPIODrvice_fxnTable,
		.object = &gpioCC3200Objects[kREDLED],
		.hwAttrs =&gpioCC3200HWAttrs[kREDLED],
	},
};

const uint_least8_t g_GPIOCount = kMCU_COUNT;

/*
 *  =============================== I2C ===============================
 */
//< Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_ints.h"
#include "hw_i2c.h"
#include "i2c.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"

#include <i2cdrv.h>
I2CMCU_Object i2cCC3200Objects[kI2CCOUNT] = {
	{
		.bitRate = kI2C_400KHz,
	}
};

const I2CMCU_HWAttrs i2cCC3200HWAttrs[kI2CCOUNT] = {
	{
		.baseAddr = I2CA0_BASE,
		.intNum = (I2C_MASTER_INT_TIMEOUT | I2C_MASTER_INT_DATA),
		.sclPin = PIN_01,
		.sdaPin = PIN_02,
		.pin_mode = PIN_MODE_1,
		.intPriority = (~0),
		.clockEnable = PRCM_RUN_MODE_CLK,
		.peripherals =PRCM_I2CA0,
		.masterCode = NULL
	}
};

const I2C_Config I2C_config[kI2CCOUNT] = {
	{
		.fxnTablePtr = &I2C_Drvice_fxnTable,
		.object =&i2cCC3200Objects[kI2CNAME_TMP006],
		.hwAttrs =&i2cCC3200HWAttrs[kI2CNAME_TMP006],
	}
};

const uint_least8_t g_I2CCount = kI2CCOUNT;
