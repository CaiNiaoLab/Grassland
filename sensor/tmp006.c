/*
 * tmp006.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月12日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "tmp006.h"

//< The constants used to calculate object temperature.
#define T_REF                   298.15
#define A1                      1.75e-03
#define A2                      -1.678e-05
#define B0                      -2.94e-05
#define B1                      -5.70e-07
#define B2                      4.63e-09
#define C2                      13.4

//< IIC 数据搬运数据结构
static I2C_Transaction g_Transaction;

uint_fast8_t TMP006_Open(TMP006 *psInst) {
	uint16_t usManufacID, usDevID;
	psInst->pui8TxData[0] = kMANUFACTURER_ID;
	g_Transaction.writeCount = 1;
	g_Transaction.readCount = 2;

	if (I2C_Device_Transfer(psInst->ui8SensorNum, &g_Transaction) == false) {
		return (false);
	} else {
		usManufacID = ((uint16_t) psInst->pui8RxData[0] << 8)
				| psInst->pui8RxData[1];
		printf("Manufacturer ID: 0x%x\n\r", usManufacID);
	}
	if (usManufacID != TMP006_MANUFAC_ID) {
		printf("Error in Manufacturer ID\n\r");
		return (false);
	}

	psInst->pui8TxData[0] = kDEVICEID;
	g_Transaction.writeCount = 1;
	g_Transaction.readCount = 2;

	if (I2C_Device_Transfer(psInst->ui8SensorNum, &g_Transaction) == false) {
		return (false);
	} else {
		usDevID = ((uint16_t) psInst->pui8RxData[0] << 8)
				| psInst->pui8RxData[1];
		printf("Device ID: 0x%x\n\r", usDevID);
	}
	if (usDevID != TMP006_DEVICE_ID) {
		printf("Error in Device ID\n");
		return (false);
	}

	return (true);
}

uint_fast8_t TMP006_Init(TMP006 *psInst, uint_fast8_t ui8Sensor,
		uint_fast8_t ui8Addr) {
	uint16_t usConfigReg;

	psInst->ui8Addr = ui8Addr;
	psInst->ui8SensorNum = ui8Sensor;

	//< Set the calibration factor to a reasonable estimate, applications
	//< should perform a calibration in their environment and directly overwrite
	//< this value after calling TMP006Init with the system specific value.
	psInst->fCalibrationFactor = 6.40e-14;

	g_Transaction.slavAddress = psInst->ui8Addr;
	g_Transaction.writeBuf = psInst->pui8TxData;
	g_Transaction.writeCount = 3;
	g_Transaction.readBuf = psInst->pui8RxData;
	g_Transaction.readCount = 0;

	if (TMP006_Open(psInst)) {
		psInst->pui8TxData[0] = kCONFIGURATION;
		g_Transaction.writeCount = 1;
		g_Transaction.readCount = 2;

		if (I2C_Device_Transfer(psInst->ui8SensorNum, &g_Transaction)
				== false) {
			return (false);
		} else {
			usConfigReg = ((uint16_t) psInst->pui8RxData[0] << 8)
					| psInst->pui8RxData[1];
			printf("Configuration register value: 0x%x\n\r", usConfigReg);
		}
	}

	return (true);
}

uint_fast8_t TMP006_Read(void) {
	return (0);
}

uint_fast8_t TMP006_Write(void) {
	return (0);
}

uint_fast8_t TMP006_DataRead(TMP006 *psInst) {
	psInst->pui8TxData[0] = kVOBJECT;
	g_Transaction.writeCount = 1;
	g_Transaction.readCount = 2;
	g_Transaction.readBuf = &psInst->pui8RxData[0];

	if (I2C_Device_Transfer(psInst->ui8SensorNum, &g_Transaction) == false) {
		return (false);
	}

	psInst->pui8TxData[0] = kTAMBIENT;
	g_Transaction.writeCount = 1;
	g_Transaction.readCount = 2;
	g_Transaction.readBuf = &psInst->pui8RxData[2];

	if (I2C_Device_Transfer(psInst->ui8SensorNum, &g_Transaction) == false) {
		return (false);
	}
	return (true);
}

void TMP006_DataTemperatureGetRaw(TMP006 *psInst, int16_t *pi16Ambient,
		int16_t *pi16Object) {
	//< Return the raw temperature value.
	*pi16Object = ((int16_t) psInst->pui8RxData[0] << 8)
			| psInst->pui8RxData[1];
	*pi16Ambient = ((int16_t) psInst->pui8RxData[2] << 8)
			| psInst->pui8RxData[3];
	//< Todo:需要加一个温度正负判断
}

void TMP006_DataTemperatureGetFloat(TMP006 *psInst, float *pfAmbient,
		float *pfObject) {
	float fTdie2, fS, fVo, fVx, fObj;
	int16_t i16Ambient;
	int16_t i16Object;

	//< Get the raw readings.
	TMP006_DataTemperatureGetRaw(psInst, &i16Ambient, &i16Object);

	//< The bottom two bits are not temperature data, so discard them but keep
	//< the sign information.
	*pfAmbient = (float) (i16Ambient / 4);

	//< Divide by 32 to get unit scaling correct.
	*pfAmbient = *pfAmbient / 32.0;

	//< fTdie2 is measured ambient temperature in degrees Kelvin.
	fTdie2 = *pfAmbient + T_REF;

	//< S is the sensitivity.
	fS =
			psInst->fCalibrationFactor
					* (1.0f + (A1 * (*pfAmbient))
							+ (A2 * ((*pfAmbient) * (*pfAmbient))));

	//< Vos is the offset voltage.
	fVo = B0 + (B1 * (*pfAmbient)) + (B2 * ((*pfAmbient) * (*pfAmbient)));

	//< Vx is the difference between raw object voltage and Vos
	//< 156.25e-9 is nanovolts per least significant bit from the voltage
	//< register.
	fVx = (((float) i16Object) * 156.25e-9) - fVo;

	//< fObj is the feedback coefficient.
	fObj = fVx + C2 * (fVx * fVx);

	//< Finally calculate the object temperature.
	*pfObject = (sqrtf(sqrtf((fTdie2 * fTdie2 * fTdie2 * fTdie2) + (fObj / fS)))
			- T_REF);
}

CTOR(TMP006)
	FUNCTION_SETTING(Init, TMP006_Init);
	FUNCTION_SETTING(Read, TMP006_Read);
	FUNCTION_SETTING(Write, TMP006_Write);
	FUNCTION_SETTING(Open, TMP006_Open);
	FUNCTION_SETTING(DataRead, TMP006_DataRead);
	FUNCTION_SETTING(DataTemperatureGetFloat, TMP006_DataTemperatureGetFloat);
	FUNCTION_SETTING(DataTemperatureGetRaw, TMP006_DataTemperatureGetRaw);
END_CTOR
