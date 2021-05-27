/*
 * lab3.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lab.h"

#include "os_config.h"

//< os include
#include "list.h"

#if LAB_3_1

//< 定义链表的根节点
struct ListNode xList_Test;

//< 定义节点
struct ListNode xList_Item1;
struct ListNode xList_Item2;
struct ListNode xList_Item3;

int lab3main(void) {
    //< 根节点初始化
    vList_Initialise(&xList_Test);

    vList_Insert_After(&xList_Test, &xList_Item1);

    vList_Insert_Before(&xList_Test, &xList_Item2);

    vList_Insert_Before(&xList_Item2, &xList_Item3);

    vList_Remove(&xList_Item1);
    return true;
}
#else
int lab3main(void) {
    return false;
}
#endif
