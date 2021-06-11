/*
 * lab.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <micrortos_config.h>
#include "lab.h"
#include "stdio.h"
#if LAB_4_1
int lab4main(void) {
    /*
     * < 条件执行，if-else 代码，看汇编和内核变化
     */
    int y = 1;
    int x = 100;
    if (y == 0x12c) {
        x++;
    } else {
        x--;
    }
    return x;
}
#elif LAB_4_2
#define LED_DELAY           800000
#define NVIC_INT_CTRL       0xE000ED04          //< 中断控制及状态寄存器
#define NVIC_PENDSVSET      0x10000000          //< 触发软件中断的值
#define NVIC_SYSPRI2        0xE000ED22          //< 系统优先级寄存器
#define NVIC_PENDSV_PRI     0x000000FF          //< 配置优先级

uint32_t * g_pCurr_task;                        //< 当前任务：记录当前是哪个任务正在运行
uint32_t * g_pNext_task;                        //< 下一个将即运行的任务指针
uint32_t * g_pPSPTaskStack[2];                  //< 任务表
uint32_t task0;                                 //< 任务1编号
uint32_t task1;                                 //< 任务2编号
uint32_t PSP_array[2];                          //< 每个任务进程栈指针
long long task0_stack[1024], task1_stack[1024]; //< 每个任务使用的任务栈

/*
 * < 任务调度接口
 */
static void taskSched(void) {
    /*
     * < 一共有两个任务。选择另一个任务，然后切换过去
     */
    if (g_pCurr_task == g_pPSPTaskStack[0]) {
        g_pNext_task = g_pPSPTaskStack[1];
    }else{
        g_pNext_task = g_pPSPTaskStack[0];
    }
    HWREG32(NVIC_INT_CTRL) = NVIC_PENDSVSET;    //< 向NVIC_INT_CTRL写NVIC_PENDSVSET，用于PendSV
}

static void delay (uint32_t count) {
    while (--count > 0);
}

static void task0Entry(void) {
    for (;;){
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        delay(LED_DELAY);
        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        taskSched();
    }
}

static void task1Entry(void){
    for (;;){
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        delay(LED_DELAY);
        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
        taskSched();
    }
}

static void led_RGB_Init(void) {
    /*
     * < P2.0 P2.1 P2.2 Init
     */
    GPIO_setAsOutputPin(
            GPIO_PORT_P2,
            GPIO_PIN0|GPIO_PIN1|GPIO_PIN2
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN0|GPIO_PIN1|GPIO_PIN2
            );
}

static void port_P1_Init(void) {
    /*
     * < Configuring LED GPIO
     */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

static void hardware_Init(void) {
    /*
     * < stop watchdog timer
     */
    WDT_A_hold(WDT_A_BASE);

    /*
     * < 加入初始化代码
     */
    port_P1_Init();
    led_RGB_Init();
}

int lab4main (void){

    hardware_Init();

    /*
     * < 1. 创建任务0的栈帧
     * < 2. 初始化程序计数器
     * < 3. 初始化xPSR 寄存器， 是处理器进入thumb状态
     */
    PSP_array[0] = ((uint32_t) task0_stack) + (sizeof task0_stack) - 16*4;
    HWREG32((PSP_array[0] + (14 << 2))) = (unsigned long)task0Entry;
    HWREG32((PSP_array[0] + (15 << 2))) = 0x01000000;
    task0 =(PSP_array[0]);                      //< 保存最终的值

    /*
     * < 1. 创建任务1的栈帧
     * < 2. 初始化程序计数器
     * < 3. 初始化xPSR 寄存器， 是处理器进入thumb状态
     */
    PSP_array[1] = ((uint32_t) task1_stack) + (sizeof task1_stack) - 16*4;
    HWREG32((PSP_array[1] + (14 << 2))) = (unsigned long)task1Entry;
    HWREG32((PSP_array[1] + (15 << 2))) = 0x01000000;
    task1 =(PSP_array[1]);

    /*
     * < 将任务加入到任务表中
     */
    g_pPSPTaskStack[0] = &task0;
    g_pPSPTaskStack[1] = &task1;

    /*
     * < 先运行tTask0
     */
    g_pNext_task = g_pPSPTaskStack[0];

    /*
     * < 运行PendSV中断
     */
    MAP_Interrupt_setPriority(FAULT_PENDSV, 0xFF);//< 向NVIC_SYSPRI2写NVIC_PENDSV_PRI，设置其为最低优先级
    HWREG32(NVIC_INT_CTRL) = NVIC_PENDSVSET;      //< 向NVIC_INT_CTRL写NVIC_PENDSVSET，用于PendSV
    return 0;
}
#endif
