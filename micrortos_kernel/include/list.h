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

#if LAB_3_1
#define LAB_3_1                     (1)
#endif

#if LAB_3_2
#define LAB_3_2                     (1)
#endif

#if LAB_3_1
struct ListNode {
    struct ListNode* pNext;        //< 指向上一个节点
    struct ListNode* pPrev;        //< 指向下一个节点
};
typedef struct ListNode listTable;

void vList_Initialise(listTable * const plist);
void vList_Insert_After(listTable * pHeadList, listTable * pNewNode);
void vList_Insert_Before(listTable * pHeadList, listTable * pNewNode);
void vList_Remove(listTable * pDeleteNode);
#elif LAB_3_2
/*< 链表节点数据结构定义
 * */
struct ListTable {
    TickType_t xItemValue;           //< 辅助值，用于帮助节点进行顺序排序
    struct ListTable* pNext;        //< 指向上一个节点
    struct ListTable* pPrev;        //< 指向下一个节点
    void * pOwner;                   //< 指向拥有该节点的内核对象，通常是TCB
    void * pContainer;               //< 指向该节点所在的链表
};
typedef struct ListTable ListTable_t;

struct MiniListNode {
    TickType_t xItemValue;
    struct ListTable* pNext;         //< 指向上一个节点
    struct ListTable* pPrev;         //< 指向下一个节点
};
typedef struct MiniListNode MiniListNode_t;
/*< 链根节点数据结构定义
 * */
typedef struct ListRoot {
    UBaseType_t uxNumberOfListRoot; //< 链表节点计数器
    ListTable_t * pIndex;           //< 链表节点索引指针
    MiniListNode_t xListEnd;        //< 链表最后一个节点
}List_t;

void vListInitialiseItem(ListTable_t * const pList);
void vListInitialise(List_t * const pList);
void vListInsertEnd(List_t * const pList, ListTable_t * const pNewList);
void vListInsert(List_t * const pList, ListTable_t * const pNewList);
UBaseType_t uListRemove(ListTable_t * const pItemToRemove);
#endif


#ifdef __cplusplus
}
#endif


#endif /* Z_OS_KERNEL_LIST_H_ */
