/*
 * lab1.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lab.h"

#include "os_config.h"

#if LAB_1
static void led_RGB_Init(void);
static void hardware_Init(void);

static void led_RGB_Init(void) {
    //< P2.0 P2.1 P2.2 Init
    GPIO_setAsOutputPin(
            GPIO_PORT_P2,
            GPIO_PIN0|GPIO_PIN1|GPIO_PIN2
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN0|GPIO_PIN1|GPIO_PIN2
            );
}

static void hardware_Init(void) {
    //< stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    led_RGB_Init();
}

static void led_RED_Blink(void) {
    volatile uint32_t i;

    // High P2.0 output
    GPIO_setOutputHighOnPin(
        GPIO_PORT_P2,
        GPIO_PIN0
        );

    // Delay
    for(i=100000; i>0; i--);

    // Low P2.0 output
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN0
        );

    for(i=100000; i>0; i--);
}

static void led_GREEN_Blink(void) {
    volatile uint32_t i;

    // High P2.1 output
    GPIO_setOutputHighOnPin(
        GPIO_PORT_P2,
        GPIO_PIN1
        );

    // Delay
    for(i=100000; i>0; i--);

    // Low P2.1 output
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN1
        );

    for(i=100000; i>0; i--);
}

static void led_BLUE_Blink(void) {
    volatile uint32_t i;

    // High P2.2 output
    GPIO_setOutputHighOnPin(
        GPIO_PORT_P2,
        GPIO_PIN2
        );

    // Delay
    for(i=100000; i>0; i--);

    // Low P2.2 output
    GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN2
        );

    for(i=100000; i>0; i--);
}


int lab1main(void){

    //< hardware init
    hardware_Init();

    while(1) {
        //< 处理事件1
        led_RED_Blink();

        //< 处理事件2
        led_GREEN_Blink();

        //< 处理事件3
        led_BLUE_Blink();
    }
}
#else
int lab1main(void){
    return false;
}
#endif
