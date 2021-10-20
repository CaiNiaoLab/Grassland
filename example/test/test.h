/*
 * test.h
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年9月8日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TEST_H_
#define TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

//< test enable
#define TMP006_TEST_ENABLE          (0)
#define KERNEL_TEST_ENABLE          (0)
#define UORBC_TEST_ENABLE           (1)

//< extern function
int tmp006_test(void);
int kernel_test(void);
int uorbc_test(void);

#ifdef __cplusplus
}
#endif
#endif /* TEST_H_ */
