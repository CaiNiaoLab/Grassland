/*
 * uorb.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月19日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: GPL-3.0 License
 */
#include "uorbc.h"
#include "topic.h"

static void uorbc_publish(UorbC_Handle handle, void *data, uint16_t len);
static void uorbc_subscribe(UorbC_Handle handle, void *data, uint16_t len);

UorbC_FxnTable UorbC_fxnTable = {
        uorbc_publish,
        uorbc_subscribe
};

MSG_DATA msg_data[KTOPIC_COUNT] = {
        {
                .data = &topic_tmp006_object,
        },
};

const UorbC_Config UorbC_config[KTOPIC_COUNT] = {
        {
                .fxnTablePtr = &UorbC_fxnTable,
                .object = &msg_data[kTOPIC_TMP006],
        },
};

static void uorbc_publish(UorbC_Handle handle, void *data, uint16_t len) {
    MSG_DATA *object = (MSG_DATA*) handle->object;
    memcpy(data, (void*) object->data, len);
}

static void uorbc_subscribe(UorbC_Handle handle, void *data, uint16_t len) {
    MSG_DATA *object = (MSG_DATA*) handle->object;
    memcpy(data, (void*) object->data, len);
}

void subscribe(uint8_t index, void *msg, uint16_t len) {
    UorbC_Handle handle = NULL;
    if (index < KTOPIC_COUNT) {
        handle = (UorbC_Handle) &(UorbC_config[index]);
    }
    handle->fxnTablePtr->subFxn(handle, msg, len);
}

void publish(uint8_t index, void *msg, uint16_t len) {
    UorbC_Handle handle = NULL;
    if (index < KTOPIC_COUNT) {
        handle = (UorbC_Handle) &(UorbC_config[index]);
    }
    handle->fxnTablePtr->pubFxn(handle, msg, len);
}
