/*
 * uorb.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月19日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UORBC_H_
#define UORBC_H_

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UorbC_Config_ *UorbC_Handle;

typedef void (*UorbC_pubFxn)(UorbC_Handle handle, void *data, uint16_t len);
typedef void (*UorbC_subFxn)(UorbC_Handle handle, void *data, uint16_t len);

typedef struct UorbC_FxnTable {
    UorbC_pubFxn pubFxn;
    UorbC_subFxn subFxn;
} UorbC_FxnTable;

typedef struct UorbC_Config_ {
    UorbC_FxnTable const *fxnTablePtr;
    void *object;
} UorbC_Config;

typedef struct MSG_DATA {
    void *data;
} MSG_DATA;

void subscribe(uint8_t index, void *msg, uint16_t len);
void publish(uint8_t index, void *msg, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif /* UORBC_H_ */
