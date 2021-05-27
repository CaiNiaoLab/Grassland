/*
 * list.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef Z_OS_KERNEL_LIST_H_
#define Z_OS_KERNEL_LIST_H_


#ifdef __cplusplus
extern "C" {
#endif

struct ListNode {
    struct ListNode* pNext;        //< 指向上一个节点
    struct ListNode* pPrev;        //< 指向下一个节点
};
typedef struct ListNode listTable;

void vList_Initialise(listTable * const plist);
void vList_Insert_After(listTable * pHeadList, listTable * pNewNode);
void vList_Insert_Before(listTable * pHeadList, listTable * pNewNode);
void vList_Remove(listTable * pDeleteNode);

#ifdef __cplusplus
}
#endif


#endif /* Z_OS_KERNEL_LIST_H_ */
