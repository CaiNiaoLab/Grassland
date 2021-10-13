/*
 * kernel.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月13日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "kernel.h"
#include "kernel_timer.h"

static LIST_HEAD(timeslice_task_list);

void scheduler_run(void) {
    ListObj *node;
    TaskObj *task;

    list_for_each(node, &timeslice_task_list)
    {
        task = list_entry(node, TaskObj, timeslice_task_list);
        if (task->is_run == TASK_RUN) {
            task->task_hdl();
            task->is_run = TASK_STOP;
        }
    }
}

void scheduler_tick(void) {
    ListObj *node;
    TaskObj *task;
    
    list_for_each(node, &timeslice_task_list)
    {
        task = list_entry(node, TaskObj, timeslice_task_list);
        if (task->timer != 0) {
            task->timer--;
            if (task->timer == 0) {
                task->is_run = TASK_RUN;
                task->timer = task->timeslice_len;
            }
        }
    }
}

void scheduler_setup(void) {
    kerenl_register_init(scheduler_tick);
    kernel_timer_init();
}

unsigned int get_task_num(void) {
    return list_len(&timeslice_task_list);
}

void task_init(TaskObj *obj, void (*task_hdl)(void), unsigned int id,
        unsigned int timeslice_len) {
    obj->id = id;
    obj->is_run = TASK_STOP;
    obj->task_hdl = task_hdl;
    obj->timer = timeslice_len;
    obj->timeslice_len = timeslice_len;
}

void task_add(TaskObj *obj) {
    list_insert_before(&timeslice_task_list, &obj->timeslice_task_list);
}

void task_del(TaskObj *obj) {
    if (task_isexist(obj)) list_remove(&obj->timeslice_task_list);
    else return;
}

unsigned char task_isexist(TaskObj *obj) {
    unsigned char isexist = 0;
    ListObj *node;
    TaskObj *task;
    
    list_for_each(node, &timeslice_task_list)
    {
        task = list_entry(node, TaskObj, timeslice_task_list);
        if (obj->id == task->id) isexist = 1;
    }
    
    return isexist;
}

unsigned int get_task_timeslice_len(TaskObj *obj) {
    return obj->timeslice_len;
}
