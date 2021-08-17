/*
 * i2cdrv.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月3日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef I2CDRV_H_
#define I2CDRV_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_STATUS_SUCCESS         (0)

/*!
 * @brief  I2C transaction is in progress or returned without completing
 */
#define I2C_STATUS_INCOMPLETE      (-8)

/*!
 * @brief  I2C bus already in use by another controller. The I2C transaction
 * was therefore unable to start.
 */
#define I2C_STATUS_BUS_BUSY        (-9)

#define I2C_WAIT_FOREVER           (~(0U))

//*****************************************************************************
//
// I2C transaction time-out value.
// Set to value 0x7D. (@100KHz it is 20ms, @400Khz it is 5 ms)
//
//*****************************************************************************
#define I2C_TIMEOUT_VAL         0x7D
typedef struct I2C_Config_ *I2C_Handle;

typedef enum I2CName {
	kTMP006 = 0,

	kI2CCOUNT
} I2CName;

typedef enum {
	kI2C_100KHz = 0,
	kI2C_400KHz = 1,
	kI2C_1000KHz = 2,
	kI2C_3330KHz = 3,
	kI2C_3400KHz = 3,
} I2C_BitRate;

typedef struct {
	uint8_t *writeBuf;
	size_t writeCount;
	uint8_t *readBuf;
	size_t readCount;
	void *arg;
	volatile int_fast16_t status;
	uint8_t slavAddress;
	void *nextPtr;
} I2C_Transaction;

typedef enum {
	kI2C_MODE_BLOCKING, kI2C_MODE_CALLBACK
} I2C_TransferMode;

typedef void (*I2C_InitFxn)(I2C_Handle handle);

typedef void (*I2C_CallbackFxn)(I2C_Handle handle, I2C_Transaction *transaction,
		bool transferStatus);
typedef int_least16_t (*I2C_TransferFxn)(I2C_Handle handle,
		I2C_Transaction *transaction, uint32_t timeout);

typedef struct {
	I2C_InitFxn initFxn;
	I2C_TransferFxn transferFxn;
} I2C_FxnTable;

typedef struct {
	uint8_t masterCode;
	uint32_t baseAddr;
	uint32_t intNum;
	uint32_t sclPin;
	uint32_t sdaPin;
	uint32_t intPriority;
	uint32_t pin_mode;
	uint32_t clockEnable;
	uint32_t peripherals;
} I2CMCU_HWAttrs;

typedef struct {
	I2C_TransferMode transferMode;
	I2C_CallbackFxn transferCallbackFxn;
	I2C_Transaction *currentTransaction;
	I2C_Transaction *volatile headPtr;
	I2C_Transaction *tailPtr;

	//< pointers to transaction buffers
	const uint8_t *writeBuf;
	uint8_t *readBuf;

	//< read, write, and burst counters
	size_t writeCount;
	size_t readCount;
	uint16_t burstCount;
	int_fast16_t status;
	bool burstStarted;

	I2C_BitRate bitRate;

	bool isOpen;
} I2CMCU_Object;

typedef struct I2C_Config_ {
	I2C_FxnTable const *fxnTablePtr;

	void *object;

	void const *hwAttrs;
} I2C_Config;

extern const I2C_FxnTable I2C_Drvice_fxnTable;

#ifdef __cplusplus
}
#endif
#endif /* I2CDRV_H_ */
