/*
 *  dyBoradInit.h
 *
 *  Created on: 2018年3月5日
 *      Author: Z.ChunHui DY(德研电科)
 *
 */

#ifndef DEVICES_DYBOARDINIT_H_
#define DEVICES_DYBOARDINIT_H_

//CC3200的API库文件

//GPIO和基本外设相关
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

//中断相关
#include "hw_ints.h"
#include "interrupt.h"

//编译启动文件的向量表，根据不同的IDE进入不同的函数指针数组
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif

void CC3200BoardInit(void);


#endif /* DEVICES_DYBORADINIT_H_ */
