/*
 * dyBoradInit.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月1日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef DEVICES_DYBOARDINIT_H_
#define DEVICES_DYBOARDINIT_H_

#ifdef __cplusplus
extern "C" {
#endif
//< CC3200的API库文件

//< GPIO和基本外设相关
#include <gpiodrv.h>
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "hw_common_reg.h"
#include "hw_apps_rcm.h"
#include "utils.h"

//< 中断相关
#include "hw_ints.h"
#include "interrupt.h"

//< 编译启动文件的向量表，根据不同的IDE进入不同的函数指针数组
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif

#ifdef __cplusplus
}
#endif
void CC3200BoardInit(void);


#endif /* DEVICES_DYBORADINIT_H_ */
