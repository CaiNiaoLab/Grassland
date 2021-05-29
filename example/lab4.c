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

#if LAB_4
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
#endif
