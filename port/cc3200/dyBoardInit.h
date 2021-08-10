/*
 *  dyBoradInit.h
 *
 *  Created on: 2018��3��5��
 *      Author: Z.ChunHui DY(���е��)
 *
 */

#ifndef DEVICES_DYBOARDINIT_H_
#define DEVICES_DYBOARDINIT_H_

//CC3200��API���ļ�

//GPIO�ͻ����������
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

//�ж����
#include "hw_ints.h"
#include "interrupt.h"

//���������ļ������������ݲ�ͬ��IDE���벻ͬ�ĺ���ָ������
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif

void CC3200BoardInit(void);


#endif /* DEVICES_DYBORADINIT_H_ */
