/*
 * list.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年9月13日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define offset_of(type, member)             ((size_t) &((type*)0)->member)
#define container_of(ptr, type, member)     ((type *)((char *)(ptr) - offset_of(type, member)))

typedef struct list_structure {
    struct list_structure *next;
    struct list_structure *prev;
} ListObj;

#define LIST_HEAD_INIT(name)    {&(name), &(name)}
#define LIST_HEAD(name)         ListObj name = LIST_HEAD_INIT(name)

void list_init(ListObj *list);
void list_insert_after(ListObj *list, ListObj *node);
void list_insert_before(ListObj *list, ListObj *node);
void list_remove(ListObj *node);
int list_isempty(const ListObj *list);
unsigned int list_len(const ListObj *list);

#define list_entry(node, type, member) \
    container_of(node, type, member)

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
  for (pos = (head)->next, n = pos->next; pos != (head); \
    pos = n, n = pos->next)

#ifdef __cplusplus
}
#endif

#endif // LIST_H_INCLUDED
