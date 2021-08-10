/*
 *  dyBoradInit.c
 *
 *  Created on: 2018��3��5��
 *      Author: Z.ChunHui DY(���е��)
 */

#include "dyBoardInit.h"

/*
 * Description: CC3200���ӵĳ�ʼ��
 *
 * param None
 *
 * return ��
 *
 */
void CC3200BoardInit(void)
{
//���ʹ��TI-RTOS �ɲ����Լ���ʼ��
#ifndef USE_TIRTOS

//������Ƕ�����жϿ�����(NVIC) �麯��(VTable)��ĵ�ַ
#if defined(ccs)
	//�ú�������ΪVTableָ��һ���µĻ���ַ��
	//��ʹ��IntRegister����ע���κ��жϴ������֮ǰ��
	//������ô˺���
	IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif


#endif

	//ʹ�ܴ������ж�
	IntMasterEnable();
	//����ϵͳʱ���ж�
	IntEnable(FAULT_SYSTICK);

	//��ʼ��������MCU
	PRCMCC3200MCUInit();
}

