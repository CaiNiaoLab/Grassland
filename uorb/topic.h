/*
 * topic.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年10月19日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TOPIC_H_
#define TOPIC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum TOPIC {
    kTOPIC_TMP006,
    KTOPIC_COUNT,
};

struct TOPIC_TMP006 {
    float fAmbient;
    float fObject;
};
typedef struct TOPIC_TMP006 topic_tmp006;
extern topic_tmp006 topic_tmp006_object;

#ifdef __cplusplus
}
#endif
#endif /* TOPIC_H_ */
