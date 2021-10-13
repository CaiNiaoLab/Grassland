/*
 * dyBoradInit.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月1日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "dyBoardInit.h"

void CC3200BoardInit(void) {
    //< 设置内嵌向量中断控制器(NVIC) 虚函数(VTable)表的地址
    //< 该函数用于为VTable指定一个新的基地址。
    //< 在使用IntRegister（）注册任何中断处理程序之前，
    //< 必须调用此函数
    IntVTableBaseSet((unsigned long) &g_pfnVectors[0]);

    //< 使能处理器中断
    IntMasterEnable();
    //< 启用系统时钟中断
    IntEnable(FAULT_SYSTICK);

    //< 初始化和配置MCU
    PRCMCC3200MCUInit();
}

