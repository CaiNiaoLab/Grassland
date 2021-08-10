/*
 * gpiodrv.hc
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年4月28日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef GPIODRV_H_
#define GPIODRV_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct GPIO_Config_ *GPIO_Handle;

/**
 *  \def    MCU_GPIOName
 *  \brief  Enum of GPIOs on the MCU dev board
 */
typedef enum GPIO_Name {
    kREDLED = 0,
    //kGRELED,
    kMCU_COUNT
} GPIO_Name;

typedef enum {
    kClose,
    kOpen
} GPIO_Status;

typedef enum {
    kGPIOWrite,
    kGPIORead
} GPIO_Dircetion;

/*
 * < ָ��GPIO_init()���������ض�ʵ�ֵĺ���ָ��
 */
typedef void (*GPIO_InitFxn)(GPIO_Handle handle);

typedef GPIO_Handle (*GPIO_OpenFxn) (GPIO_Handle handle);
typedef GPIO_Handle (*GPIO_CloseFxn)(GPIO_Handle handle);

typedef struct GPIOMCU_HWAttrs {
    uint64_t base_port;
    uint64_t pin_num;
    uint64_t init_pin;
} GPIOMCU_HWAttrs;

typedef struct {
    GPIO_Status gpioStatus;
    uint64_t dircetion;
    uint64_t pin_mode;
    uint64_t pin_address;
} GPIO_Object;

/*
 * < GPIO������Ķ��壬���а��������ض� GPIO ����ʵ�������һ�麯����
 */
typedef struct {
    GPIO_InitFxn initFxn;
    GPIO_OpenFxn openFxn;
    GPIO_CloseFxn closeFxn;
} GPIO_FxnTable;

/*
 * < GPIO_Config �ṹ����һ�����ڱ��� GPIO ������ʵ�ֵ�ָ�롣
 */
typedef struct GPIO_Config_ {
    GPIO_FxnTable const *fxnTablePtr;
    void                *object;
    void          const *hwAttrs;
}GPIO_Config;

extern const GPIO_FxnTable GPIODrvice_fxnTable;

#endif /* GPIODRV_H_ */
