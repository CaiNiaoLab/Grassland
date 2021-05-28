/*
 * main.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "os_config.h"

#include "lab.h"


int main(void) {

#if LAB_1
    while(lab1main())
        ;
#endif
#if LAB_2
    while(lab2main())
        ;
#endif
#if (LAB_3_1 || LAB_3_2)
    while(lab3main())
        ;
#endif
}
