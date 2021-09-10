/*
 * sensor_management.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月20日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "sensor_management.h"
#include "tmp006.h"

#define SENSOR_NUM(sensor) (sizeof(sensor)/sizeof(sensor[0]))

/*
 *  ======================= TMP006 sensor config ==============================
 */
//< TMP006传感器变量
static TMP006 *g_sTMP006Inst;
static bool g_IsInitialized = false;
static bool g_TMP006_Status = false;

/*
 *  ============================= sensor config ==============================
 */
static void Sensor_TMP006_init(Sensor_Handle handle);
static bool Sensor_TMP006_Read(Sensor_Handle handle, float *data);
static Sensor_Handle Sensor_TMP006_write(Sensor_Handle handle);
static uint8_t Sensor_Device_parse(const char *data, size_t dataLen);

Sensor_FxnTable Sensor_fxnTable[kSENSOR_TYPE_CONUT] = {
		{
			Sensor_TMP006_init,
			Sensor_TMP006_Read,
			Sensor_TMP006_write,
			Sensor_Device_parse,
		},

};
Sensor_Object sensor_object[kSENSOR_TYPE_CONUT] = {
		{
				.userType = SENSOR_USER_TMP006,
				.ui8SensorNum = kADDRPIN_ADR0,
		},
};

const Sensor_HWAttr sensor_HWAttrs[kSENSOR_TYPE_CONUT] = {
		{
				.type = kTMP,
				.deviceType = IIC,
		}
};

const Sensor_Config Sensor_config[kSENSOR_TYPE_CONUT] = {
		{
				.fxnTablePtr = &Sensor_fxnTable[kTMP006],
				.object = &sensor_object[kTMP006],
				.hwAttrs = &sensor_HWAttrs[kTMP006],
		}
};

static void Sensor_TMP006_init(Sensor_Handle handle){
	Sensor_Object *object = handle->object;

	g_sTMP006Inst = TMP006_new();

	g_sTMP006Inst->Init(g_sTMP006Inst, \
					object[SENSOR_USER_TMP006].userType, \
					object[SENSOR_USER_TMP006].ui8SensorNum);

}

static bool Sensor_TMP006_Read(Sensor_Handle handle, float *dataAddr){

	float fAmbient, fObject;

	g_TMP006_Status = g_sTMP006Inst->DataRead(g_sTMP006Inst);
	if(g_TMP006_Status) {
		g_sTMP006Inst->DataTemperatureGetFloat(g_sTMP006Inst, \
				&fAmbient, &fObject);
		dataAddr[0] = fAmbient;
		dataAddr[1] = fObject;
	}

	return (g_TMP006_Status);
}
static Sensor_Handle Sensor_TMP006_write(Sensor_Handle handle){
	return NULL;
}
static uint8_t Sensor_Device_parse(const char *data, size_t dataLen){
	return NULL;
}

//< 外部调用接口
void Sensor_Init(void){
	uint8_t i;

	if(!g_IsInitialized){
		g_IsInitialized = (bool)true;

		for(i = 0; i < kSENSOR_TYPE_CONUT; i++){
			Sensor_config[i].fxnTablePtr->initFxn((Sensor_Handle)&(Sensor_config[i]));
		}
	}
}

<<<<<<< HEAD
=======
/*
 * 读取float类型数据
 */
>>>>>>> main
bool Sensor_Read_Float(uint8_t index, float *dataAddr){
	Sensor_Handle handle = NULL;
	bool result;
	if (g_IsInitialized && (index < kSENSOR_TYPE_CONUT)) {
		handle = (Sensor_Handle) &(Sensor_config[index]);
	}

	result = handle->fxnTablePtr->readFxn(handle,dataAddr);
	if (result == true) {
		return (true);
	} else {
		return (false);
	}
}

bool Sensor_Write_Data(uint8_t index, uint8_t *data){
	Sensor_Handle handle = NULL;

	return handle;
}
