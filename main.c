/* main.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*
 * Soft Framework
 * LAB_1: 轮询系统实现
 * LAB_2: 前后台系统
 * */
#define     LAB_1           (0)
#define     LAB_2           (1)


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


int main(void){

    //< hardware init
    hardware_Init();

    while(1) {
        //< �����¼�1
        led_RED_Blink();

        //< �����¼�2
        led_GREEN_Blink();

        //< �����¼�3
        led_BLUE_Blink();
    }
}
#endif


#if LAB_2
static void led_RGB_Init(void);
static uint8_t flag1 = 0;
static uint8_t flag2 = 0;
static uint8_t flag3 = 0;

static void clock_System_Init(void) {
    //< ѡ�� MCLK ��Ϊʱ��Դ
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);
}

static void timer32_Init(void) {
    MAP_Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                        TIMER32_PERIODIC_MODE);
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);
}

static void port_P1_Init() {
    //< Configuring LED GPIO
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    //< Configuring Switch GPIO, P1.1 & P1.4
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    //< Enabling Port1 interrupts
    MAP_Interrupt_enableInterrupt(INT_PORT1);
}

static void hardware_Init(void) {
    //< stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    MAP_Interrupt_disableMaster();

    //< TODO: �����ʼ������
    clock_System_Init();
    timer32_Init();
    port_P1_Init();
    led_RGB_Init();
    MAP_Interrupt_enableMaster();

}

static void Led_RGB_Close(void) {
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN0|GPIO_PIN1|GPIO_PIN2
            );
}

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

static void led_RED_Blink(void) {
    // High P2.0 output
    MAP_GPIO_toggleOutputOnPin(
        GPIO_PORT_P2,
        GPIO_PIN0
        );
}

static void led_GREEN_Blink(void) {
    // High P2.1 output
    MAP_GPIO_toggleOutputOnPin(
        GPIO_PORT_P2,
        GPIO_PIN1
        );
}

static void led_BLUE_Blink(void) {
    // High P2.2 output
    MAP_GPIO_toggleOutputOnPin(
        GPIO_PORT_P2,
        GPIO_PIN2
        );
}

int main(void) {
    //< hardware init
    hardware_Init();

    while (1) {
        if (flag1 == 1) {
            flag1 = 0;
            led_RED_Blink();
        }
        if (flag2 == 2) {
            flag2 = 0;
            led_GREEN_Blink();
        }
        if (flag3 == 4) {
            flag3 = 0;
            led_BLUE_Blink();
        }

        MAP_PCM_gotoLPM0();
    }
}

void PORT1_IRQHandler(void) {
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (GPIO_PIN1 & status) {
        MAP_GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
        MAP_Timer32_setCount(TIMER32_BASE, 128000);
        MAP_Timer32_enableInterrupt(TIMER32_BASE);
        MAP_Timer32_startTimer(TIMER32_BASE, true);
    } else if (GPIO_PIN4 & status) {
        flag1 = 0;
        flag2 = 0;
        flag3 = 0;
        Led_RGB_Close();
        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        MAP_GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
        MAP_Timer32_disableInterrupt(TIMER32_BASE);
        MAP_Timer32_startTimer(TIMER32_BASE, false);
    }
}

void T32_INT1_IRQHandler(void) {
    MAP_Timer32_clearInterruptFlag(TIMER32_BASE);
    MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

    flag1 ++;
    flag2 ++;
    flag3 ++;

    MAP_Timer32_setCount(TIMER32_BASE, 128000);
    MAP_Timer32_enableInterrupt(TIMER32_BASE);
    MAP_Timer32_startTimer(TIMER32_BASE, true);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1|GPIO_PIN4);
}
#endif
