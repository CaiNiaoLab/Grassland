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
#include "portmacro.h"
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
#elif LAB_3_2
struct ListRoot     g_List_Test;            //< 定义根节点

struct ListTable    g_List_Item1;           //< 定义用户节点
struct ListTable    g_List_Item2;           //< 定义用户节点
struct ListTable    g_List_Item3;           //< 定义用户节点

int lab3main(void) {

    /* 根节点初始化 */
    vListInitialise(&g_List_Test);

    vListInitialiseItem(&g_List_Item1);     //< 节点1初始化
    g_List_Item1.xItemValue = 1;
    vListInitialiseItem(&g_List_Item2);     //< 节点2初始化
    g_List_Item2.xItemValue = 2;
    vListInitialiseItem(&g_List_Item3);     //< 节点3初始化
    g_List_Item3.xItemValue = 3;

    /* 将节点插入链表， 按照升序排序 */
    vListInsert(&g_List_Test, &g_List_Item2);
    vListInsert(&g_List_Test, &g_List_Item1);
    vListInsert(&g_List_Test, &g_List_Item3);

    uListRemove(&g_List_Item2);
    return true;
}
#else
int lab3main(void) {
    return false;
}
#endif
