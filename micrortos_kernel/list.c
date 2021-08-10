/*
 * list.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <micrortos_config.h>
#include <list.h>
#include <stdlib.h>

#if LAB_3_1
void vList_Initialise(listTable * const plist) {
    plist->pNext = plist->pPrev = plist;
}

void vList_Insert_After(listTable * pHeadList, listTable * pNewNode) {
    pHeadList->pNext->pPrev = pNewNode;     //< pHeadList(表头节点)里面下一个节点的上一个节点地址指向 pNewNode(新的节点)
    pNewNode->pNext = pHeadList->pNext;     //< pNewNode(新的节点)里面下一个节点地址是  pHeadList(表头节点)原来节点的下一个节点地址

    pHeadList->pNext = pNewNode;            //< pHeadList(表头节点)里面下一个节点地址是 pNewNode(新的节点)
    pNewNode->pPrev = pHeadList;            //< pNewNode(新的节点)里面上一个节点地址是 pHeadList(表头节点)
}

void vList_Insert_Before(listTable * pHeadList, listTable * pNewNode) {
    pHeadList->pPrev->pNext = pNewNode;
    pNewNode->pPrev = pHeadList->pPrev;

    pHeadList->pPrev = pNewNode;
    pNewNode->pNext = pHeadList;
}

void vList_Remove(listTable * pDeleteNode) {
    pDeleteNode->pNext->pPrev = pDeleteNode->pPrev;
    pDeleteNode->pPrev->pNext = pDeleteNode->pNext;

    pDeleteNode->pNext = pDeleteNode->pPrev = pDeleteNode;
}
#elif LAB_3_2
/*
 * < 链表节点的初始化
 */
void vListInitialiseItem(ListTable_t * const pList) {
    pList->pContainer = NULL;   //< List is null, do not have any lists
}

/*
 * < 链表根节点初始化
 */
void vListInitialise(List_t * const pList) {
    /* 将链表索引指针指向最后一个节点 */
    pList->pIndex = ( ListTable_t * ) & ( pList->xListEnd );

    /* 将链表最后一个节点辅助排序值设置最大 */
    pList->xListEnd.xItemValue = portMAX_DELAY;

    /* 将最后一个pNext 和  pPrev 指针均指向自身节点，表示链表为空  */
    pList->xListEnd.pNext = ( ListTable_t * ) & (pList->xListEnd );
    pList->xListEnd.pPrev = ( ListTable_t * ) & (pList->xListEnd );

    /* 初始化节点计数器的值为 0，表示链表为空 */
    pList->uxNumberOfListRoot = ( UBaseType_t ) 0U;
}

/*
 * < 节点插入链表的尾部
 */
void vListInsertEnd(List_t * const pList, ListTable_t * const pNewList) {
    ListTable_t * const pIndex = pList->pIndex;

    pNewList->pNext      = pIndex;
    pNewList->pPrev      = pIndex->pPrev;

    pIndex->pPrev->pNext = pNewList->pNext;
    pIndex->pPrev        = pNewList;

    pIndex->pContainer   = (void *)pList;   //< 节点所在链表

    (pList->uxNumberOfListRoot) ++;         //< 链表节点计数器加一
}

/*
 * < 节点按照升序排序插入链表
 */
void vListInsert(List_t * const pList, ListTable_t * const pNewList) {
    ListTable_t *pIterator;

    /* 获取节点的排序辅助值 */
    const TickType_t xValueOfInsertion = pNewList->xItemValue;

    /* 寻找节点要插入的位置  */
    if (xValueOfInsertion == portMAX_DELAY) {
        pIterator = pList->xListEnd.pPrev;
    } else {
        /* 倒序遍历链表，寻找要插入的位置 */
        for ( pIterator = (ListTable_t *) & (pList->xListEnd); \
              pIterator->pPrev->xItemValue <= xValueOfInsertion; \
              pIterator = pIterator->pNext) {
            }
    }

    /* 根据升序排序， 将节点插入链表 */
    pNewList->pNext = pIterator->pNext;
    pNewList->pNext->pPrev = pNewList;
    pNewList->pPrev = pIterator;
    pIterator->pNext = pNewList;

    /* 指向根节点 */
    pNewList->pContainer = (void *) pList;

    /* 链表节点计数器加一 */
    (pList->uxNumberOfListRoot)++;
}

/*
 * < 将节点从链表中删除
 */
UBaseType_t uListRemove(ListTable_t * const pItemToRemove) {
    List_t * const pList = (List_t *)pItemToRemove->pContainer;

    /* 将指定节点从链表中删除 */
    pItemToRemove->pNext->pPrev = pItemToRemove->pPrev;
    pItemToRemove->pPrev->pPrev = pItemToRemove->pNext;

    /* 调整链表节点索引指针 */
    if (pList->pIndex == pItemToRemove) {
        pList->pIndex = pItemToRemove->pPrev;
    }

    /* 将根节点计数值调整为空 */
    pItemToRemove->pContainer = NULL;

    /* 链表节点计数器减一 */
    ( pList->uxNumberOfListRoot ) --;

    return pList->uxNumberOfListRoot;
}
#endif
