/*
 * kernel_timer.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月13日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */

#ifndef PORT_CC3200_DRIVE_KERNEL_TIMER_H_
#define PORT_CC3200_DRIVE_KERNEL_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SYS_CLK                 80000000
#define MILLISECONDS_TO_TICKS(ms)   ((SYS_CLK/1000) * (ms))
#define MICROSECONDS_TO_TICKS(us)   ((SYS_CLK/1000000) * (us))
#define SLOW_TIMER_DELAY_uS   2000

typedef void (*kernel_register)(void);


extern void Timer_IF_Init(unsigned long ePeripheralc, unsigned long ulBase,
        unsigned long ulConfig, unsigned long ulTimer, unsigned long ulValue);
extern void Timer_IF_IntSetup(unsigned long ulBase, unsigned long ulTimer,
        void (*TimerBaseIntHandler)(void));
extern void Timer_IF_InterruptClear(unsigned long ulBase);
extern void Timer_IF_Start(unsigned long ulBase, unsigned long ulTimer,
        unsigned long ulValue);
extern void Timer_IF_Stop(unsigned long ulBase, unsigned long ulTimer);

extern void kernel_timer_init(void);
extern void kerenl_register_init(kernel_register kernel_tick);
#ifdef __cplusplus
}
#endif
#endif /* PORT_CC3200_DRIVE_KERNEL_TIMER_H_ */
