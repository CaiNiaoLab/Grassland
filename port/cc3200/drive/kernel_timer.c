/*
 * kernel_timer.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月13日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "kernel_timer.h"

#include "stdlib.h"

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "timer.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"

static unsigned char GetPeripheralIntNum(unsigned long ulBase,
        unsigned long ulTimer) {
    if (ulTimer == TIMER_A) {
        switch (ulBase) {
        case TIMERA0_BASE:
            return INT_TIMERA0A;
        case TIMERA1_BASE:
            return INT_TIMERA1A;
        case TIMERA2_BASE:
            return INT_TIMERA2A;
        case TIMERA3_BASE:
            return INT_TIMERA3A;
        default:
            return INT_TIMERA0A;
        }
    } else if (ulTimer == TIMER_B) {
        switch (ulBase) {
        case TIMERA0_BASE:
            return INT_TIMERA0B;
        case TIMERA1_BASE:
            return INT_TIMERA1B;
        case TIMERA2_BASE:
            return INT_TIMERA2B;
        case TIMERA3_BASE:
            return INT_TIMERA3B;
        default:
            return INT_TIMERA0B;
        }
    } else {
        return INT_TIMERA0A;
    }
    
}

void Timer_IF_Init(unsigned long ePeripheral, unsigned long ulBase, unsigned
long ulConfig, unsigned long ulTimer, unsigned long ulValue) {
    //
    // Initialize GPT A0 (in 32 bit mode) as periodic down counter.
    //
    MAP_PRCMPeripheralClkEnable(ePeripheral, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralReset(ePeripheral);
    MAP_TimerConfigure(ulBase, ulConfig);
    MAP_TimerPrescaleSet(ulBase, ulTimer, ulValue);
}

void Timer_IF_IntSetup(unsigned long ulBase, unsigned long ulTimer,
        void (*TimerBaseIntHandler)(void)) {
    //
    // Setup the interrupts for the timer timeouts.
    //
    MAP_IntPrioritySet(GetPeripheralIntNum(ulBase, ulTimer),
    INT_PRIORITY_LVL_1);
    MAP_TimerIntRegister(ulBase, ulTimer, TimerBaseIntHandler);
    
    if (ulTimer == TIMER_BOTH) {
        MAP_TimerIntEnable(ulBase, TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT);
    } else {
        MAP_TimerIntEnable(ulBase,
                ((ulTimer == TIMER_A) ? TIMER_TIMA_TIMEOUT : TIMER_TIMB_TIMEOUT));
    }
}

void Timer_IF_Start(unsigned long ulBase, unsigned long ulTimer,
        unsigned long ulValue) {
    MAP_TimerLoadSet(ulBase, ulTimer, MICROSECONDS_TO_TICKS(ulValue));
    //
    // Enable the GPT
    //
    MAP_TimerEnable(ulBase, ulTimer);
}

void Timer_IF_Stop(unsigned long ulBase, unsigned long ulTimer) {
    //
    // Disable the GPT
    //
    MAP_TimerDisable(ulBase, ulTimer);
}

void Timer_IF_InterruptClear(unsigned long ulBase) {
    unsigned long ulInts;
    ulInts = MAP_TimerIntStatus(ulBase, true);
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(ulBase, ulInts);
}

kernel_register kernel_register_init_tick = NULL;

void TimerBaseIntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    Timer_IF_InterruptClear(TIMERA0_BASE);
    kernel_register_init_tick();

}

void kerenl_register_init(kernel_register kernel_tick) {
    kernel_register_init_tick = kernel_tick;
}

void kernel_timer_init(void){
    Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_A, 0);
    Timer_IF_IntSetup(TIMERA0_BASE, TIMER_A, TimerBaseIntHandler);
    Timer_IF_Start(TIMERA0_BASE, TIMER_A, 1000);
}
