/*
 * kernel.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月13日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */

#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TASK_STOP, TASK_RUN
} IsTaskRun;

typedef struct timesilce {
    unsigned int id;
    void (*task_hdl)(void);
    IsTaskRun is_run;
    unsigned int timer;
    unsigned int timeslice_len;
    ListObj timeslice_task_list;
} TaskObj;

void scheduler_setup(void);
void scheduler_run(void);

void task_init(TaskObj *obj, void (*task_hdl)(void), unsigned int id,
        unsigned int timeslice_len);
void task_add(TaskObj *obj);
void task_del(TaskObj *obj);
unsigned int get_task_timeslice_len(TaskObj *obj);
unsigned int get_task_num(void);
unsigned char task_isexist(TaskObj *obj);

#ifdef __cplusplus
}
#endif
#endif /* KERNEL_KERNEL_H_ */
