/*
 *  dyBoradInit.c
 *
 *  Created on: 2018年3月5日
 *      Author: Z.ChunHui DY(德研电科)
 */

#include "dyBoardInit.h"

/*
 * Description: CC3200板子的初始化
 *
 * param None
 *
 * return 无
 *
 */
void CC3200BoardInit(void)
{
//如果使用TI-RTOS 由操作自己初始化
#ifndef USE_TIRTOS

//设置内嵌向量中断控制器(NVIC) 虚函数(VTable)表的地址
#if defined(ccs)
	//该函数用于为VTable指定一个新的基地址。
	//在使用IntRegister（）注册任何中断处理程序之前，
	//必须调用此函数
	IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif


#endif

	//使能处理器中断
	IntMasterEnable();
	//启用系统时钟中断
	IntEnable(FAULT_SYSTICK);

	//初始化和配置MCU
	PRCMCC3200MCUInit();
}

