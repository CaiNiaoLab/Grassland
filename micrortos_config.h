/*
 * os_config.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef MICRORTOS_CONFIG_H_
#define MICRORTOS_CONFIG_H_

/*
 * Include the generic headers required for the RTOS port being used.
 */
#include <stddef.h>

/*
 * If stdint.h cannot be located then:
 *   + If using GCC ensure the -nostdint options is *not* being used.
 *   + Ensure the project's include path includes the directory in which your
 *     compiler stores stdint.h.
 *   + Set any compiler options necessary for it to support C99, as technically
 *     stdint.h is only mandatory with C99 (RTOS does not require C99 in any
 *     other way).
 *   + The FreeRTOS download includes a simple stdint.h definition that can be
 *     used in cases where none is provided by the compiler.  The files only
 *     contains the typedefs required to build RTOS.  Read the instructions
 *     in stdint.readme for more information.
 */
#include <stdint.h> /* READ COMMENT ABOVE. */

#include <micrortos_kernel/portable/ccs/ARM_CM4F/portmacro.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Soft Framework
 * LAB_1：轮询系统实现
 * LAB_2：前后台系统实现
 * LAB_3_1：双向链表插入和删除的操作
 * LAB_3_2：RTOS中的链表实现
 * LAB4: 关于Cortex-M4内核的寄存器实验
 * */
#define     LAB_1           (0)
#define     LAB_2           (0)
#define     LAB_3_1         (0)
#define     LAB_3_2         (0)
#define     LAB_4           (0)
#ifdef __cplusplus
}
#endif

#endif /* MICRORTOS_CONFIG_H_ */
