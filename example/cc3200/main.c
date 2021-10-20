/*
 * main.c
 *
 * Copyright (c) 2021, ZhaoSQ-CH.CaiNiaoLab
 * Created on: 2021年9月8日
 *     Author: ZhaoSQ-CH.CaiNiaoLab
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include "test.h"

int main(void) {
#if TMP006_TEST_ENABLE
	tmp006_test();
#endif

#if KERNEL_TEST_ENABLE
	kernel_test();
#endif

#if UORBC_TEST_ENABLE
	uorbc_test();
#endif
#if USER_DEMO_V_0_1_TEST
	user_demo_v_0_1_test();
#endif
	return 0;
}
