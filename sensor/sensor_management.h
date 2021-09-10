/*
 * sensor_management.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月20日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SENSOR_SENSOR_MANAGEMENT_H_
#define SENSOR_SENSOR_MANAGEMENT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Sensor_Config_ *Sensor_Handle;

typedef void (*Sensor_initFxn)(Sensor_Handle hanlde);
typedef bool (*Sensor_readFxn)(Sensor_Handle handle, float *dataAddr);
typedef Sensor_Handle (*Sensor_writeFxn)(Sensor_Handle handle);
typedef uint8_t (*Sensor_parseFxn)(const char *data, size_t dataLen);

//< 引入传感器类型
typedef enum{
	kTMP,
	kSENSOR_TYPE_CONUT,
}SENSOR_TYPE;

typedef enum{
	SENSOR_USER_TMP006,
	SENSOR_USER_COUNT,
}SENSOR_USER;

typedef enum{
	IIC,
	SPI,
	ADC,
	SENSOR_DEVICE_TYPE_HW_COUNT,
}SENSOR_DEVICE_HW_TYPE;
/*
 * \def SENSOR_FxnTable
 * \brief SENSOR功能表
 */
typedef struct Sensor_FxnTable{
	Sensor_initFxn initFxn;		//< sensor initial set
	Sensor_readFxn readFxn;		//< sensor read data
	Sensor_writeFxn writeFxn;	//< sensor write data
	Sensor_parseFxn parseFxn;	//< sensor parse handle
} Sensor_FxnTable;

typedef struct {
	SENSOR_USER const userType;		//< sensor type
	uint8_t ui8SensorNum;
	//< The data buffer used for sending/receiving data to/from the TMP006.
	int32_t pui8TxData[4];
	int32_t pui8RxData[4];
}Sensor_Object;

typedef struct {
	SENSOR_TYPE const type;
	SENSOR_DEVICE_HW_TYPE deviceType;
}Sensor_HWAttr;

typedef struct Sensor_Config_ {
	Sensor_FxnTable const *fxnTablePtr;
	void 				  *object;
	void 			const *hwAttrs;
}Sensor_Config;

<<<<<<< HEAD

=======
>>>>>>> main
bool Sensor_Read_Float(uint8_t index, float *dataAddr);
void Sensor_Init(void);
#ifdef __cplusplus
}
#endif
#endif /* SENSOR_SENSOR_MANAGEMENT_H_ */
