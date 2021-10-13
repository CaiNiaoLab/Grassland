/*
 * main.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年8月10日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "test.h"
#if TMP006_TEST_ENABLE
#include <stdio.h>
#include <gpiodev.h>
#include <i2cdev.h>

#include "dyBoardInit.h"
#include "sensor_management.h"

/*
 * 用于测试文件
 */
int tmp006_test(void) {
    float fAmbient, fObject;
    int_fast32_t i32IntegerPart;
    int_fast32_t i32FractionPart;
    float Data[2] = {0};
    float *DataAddr = &Data[0];

    CC3200BoardInit();
    GPIO_Device_Init();
    I2C_Device_Init();
    Sensor_Init();

    while (1) {
        GPIO_Device_Open(kREDLED);
        MAP_UtilsDelay(8000000);
        GPIO_Device_Close(kREDLED);
        MAP_UtilsDelay(8000000);

        Sensor_Read_Float(kTMP006,DataAddr);

        fAmbient = Data[0];
        i32IntegerPart = (int32_t) fAmbient;
        i32FractionPart = (int32_t) (fAmbient * 1000.0f);
        i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
        if (i32FractionPart < 0) {
            i32FractionPart *= -1;
        }
        printf("Ambient %3d.%03d\t", i32IntegerPart, i32FractionPart);

        //< Convert the floating point ambient temperature  to an integer part
        //< and fraction part for easy printing.
        fObject = Data[1];
        i32IntegerPart = (int32_t) fObject;
        i32FractionPart = (int32_t) (fObject * 1000.0f);
        i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
        if (i32FractionPart < 0) {
            i32FractionPart *= -1;
        }
        printf("Object %3d.%03d\n", i32IntegerPart, i32FractionPart);
    }
}
#endif


#if KERNEL_TEST_ENABLE
#include <stdio.h>
#include <stdbool.h>

#include "gpiodev.h"
#include "dyBoardInit.h"
#include "kernel.h"

// 创建5个任务对象
TaskObj task_1, task_2, task_3, task_4, task_5;

// 具体的任务函数
void task1_hdl(void) {
    printf(">> task 1 is running ...\n");
}

void task2_hdl(void) {
    printf(">> task 2 is running ...\n");
}

void task3_hdl(void) {
    printf(">> task 3 is running ...\n");
}

void task4_hdl(void) {
    printf(">> task 4 is running ...\n");
}

void task5_hdl(void) {
    GPIO_Device_Open(kREDLED);
    MAP_UtilsDelay(8000000);
    GPIO_Device_Close(kREDLED);
    MAP_UtilsDelay(8000000);
    printf(">> task 5 is running ...\n");
}

// 初始化任务对象，并且将任务添加到时间片轮询调度中
void all_task_init() {
    task_init(&task_1, task1_hdl, 1, 1);
    task_init(&task_2, task2_hdl, 2, 10);
    task_init(&task_3, task3_hdl, 3, 50);
    task_init(&task_4, task4_hdl, 4, 1000);
    task_init(&task_5, task5_hdl, 5, 5000);
    task_add(&task_1);
    task_add(&task_2);
    task_add(&task_3);
    task_add(&task_4);
    task_add(&task_5);
}

int kernel_test(void) {

    all_task_init();

    printf(">> task num: %d\n", get_task_num());
    printf(">> task len: %d\n", get_task_timeslice_len(&task_3));

    task_del(&task_2);
    printf(">> delet task 2\n");
    printf(">> task 2 is exist: %d\n", task_isexist(&task_2));

    printf(">> task num: %d\n", get_task_num());

    task_del(&task_5);
    printf(">> delet task 5\n");

    printf(">> task num: %d\n", get_task_num());

    printf(">> task 3 is exist: %d\n", task_isexist(&task_3));
    task_add(&task_2);
    printf(">> add task 2\n");
    printf(">> task 2 is exist: %d\n", task_isexist(&task_2));

    task_add(&task_5);
    printf(">> add task 5\n");

    printf(">> task num: %d\n", get_task_num());

    printf("\n\n========timeslice running===========\n");

    CC3200BoardInit();
    GPIO_Device_Init();
    scheduler_setup();

    while(1) {
        scheduler_run();
    }
}
#endif
