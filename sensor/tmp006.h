/*
 * tmp006.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月12日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SENSOR_TMP006_H_
#define SENSOR_TMP006_H_

#include "lw_oopc.h"

#include <i2cdev.h>

//< Reset TMP006; self clearing
#define TMP006_CONFIG_RESET_ASSERT 0x8000

#define TMP006_CONFIG_DEFAULT _ASSERT 0x7480

//< TMP006 Device details
#define TMP006_MANUFAC_ID       0x5449
#define TMP006_DEVICE_ID        0x0067

enum SlaveAddress {
	kADDRPIN_ADR0 = 0b1000001,
};

enum Register {
	kVOBJECT = 0x00,
	kTAMBIENT = 0x01,
	kCONFIGURATION = 0x02,
	kMANUFACTURER_ID = 0xFE,
	kDEVICEID = 0xFF,
};

CLASS(TMP006)
{
	//< The pointer to the I2C master interface instance used to communicate
	//< with the TMP006.
	uint8_t ui8SensorNum;
	//< The I2C address of the TMP006.
	uint8_t ui8Addr;

	//< The data buffer used for sending/receiving data to/from the TMP006.
	uint8_t pui8TxData[4];
	uint8_t pui8RxData[4];

	//< Calibration factor.  Left to application to implement calibration
	//< See term S0 in http://www.ti.com/lit/ug/sbou107/sbou107.pdf
	float fCalibrationFactor;

	uint_fast8_t (*Init)(TMP006 *psInst, uint_fast8_t ui8Sensor,
			uint_fast8_t ui8Addr);
	uint_fast8_t (*Read)(void);
	uint_fast8_t (*Write)(void);
	uint_fast8_t (*Open)(TMP006 *psInst);
	uint_fast8_t (*DataRead)(TMP006 *psInst);
	void (*DataTemperatureGetRaw)(TMP006 *psInst, int16_t *pi16Ambient,
			int16_t *pi16Object);
	void (*DataTemperatureGetFloat)(TMP006 *psInst, float *pfAmbient,
			float *pfObject);
};

#endif /* SENSOR_TMP006_H_ */
