/*
 * list.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "list.h"

void vList_Initialise(listTable * const plist){
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
