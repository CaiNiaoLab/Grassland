/*
 * list.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年9月13日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */
#include "list.h"

void list_init(ListObj *list) {
    list->next = list->prev = list;
}

void list_insert_after(ListObj *list, ListObj *node) {
    list->next->prev = node;
    node->next = list->next;
    
    list->next = node;
    node->prev = list;
}

void list_insert_before(ListObj *list, ListObj *node) {
    list->prev->next = node;
    node->prev = list->prev;
    list->prev = node;
    node->next = list;
}

void list_remove(ListObj *node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    
    node->next = node->prev = node;
}

int list_isempty(const ListObj *list) {
    return list->next == list;
}

unsigned int list_len(const ListObj *list) {
    unsigned int len = 0;
    const ListObj *p = list;
    while (p->next != list) {
        p = p->next;
        len++;
    }
    
    return len;
}
