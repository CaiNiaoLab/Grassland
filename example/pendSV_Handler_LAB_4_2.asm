	.thumb

	.ref g_pCurr_task
	.ref g_pNext_task

	.def LAB_4_2_PendSV_Handler

LAB_4_2_Curr_task:						.word	g_pCurr_task
LAB_4_2_Next_task:						.word	g_pNext_task

; -----------------------------------------------------------

	.align 4
LAB_4_2_PendSV_Handler: .asmfunc
	MRS     R0, PSP                   ; 获取当前任务的堆栈指针
    CBZ     R0, PendSVHandler_nosave  ; if 这是由tTaskSwitch触发的(此时，PSP肯定不会是0了，0的话必定是tTaskRunFirst)触发
                                      ; 不清楚的话，可以先看tTaskRunFirst和tTaskSwitch的实现
    STMDB   R0!, {R4-R11}             ; 那么，我们需要将除异常自动保存的寄存器这外的其它寄存器自动保存起来{R4, R11}
                                      ; 保存的地址是当前任务的PSP堆栈中，这样就完整的保存了必要的CPU寄存器,便于下次恢复
    LDR     R1, LAB_4_2_Curr_task     ; 保存好后，将最后的堆栈顶位置，保存到currentTask->stack处
    LDR     R1, [R1]                  ; 由于stack处在结构体stack处的开始位置处，显然currentTask和stack在内存中的起始
    STR     R0, [R1]                  ; 地址是一样的，这么做不会有任何问题

PendSVHandler_nosave                  ; 无论是tTaskSwitch和tTaskSwitch触发的，最后都要从下一个要运行的任务的堆栈中恢复
                                      ; CPU寄存器，然后切换至该任务中运行
    LDR     R0, LAB_4_2_Curr_task     ; 好了，准备切换了
    LDR     R1, LAB_4_2_Next_task
    LDR     R2, [R1]
    STR     R2, [R0]                  ; 先将currentTask设置为nextTask，也就是下一任务变成了当前任务

    LDR     R0, [R2]                  ; 然后，从currentTask中加载stack，这样好知道从哪个位置取出CPU寄存器恢复运行
    LDMIA   R0!, {R4-R11}             ; 恢复{R4, R11}。为什么只恢复了这么点，因为其余在退出PendSV时，硬件自动恢复

    MSR     PSP, R0                   ; 最后，恢复真正的堆栈指针到PSP
    ORR     LR, LR, #0x04             ; 标记下返回标记，指明在退出LR时，切换到PSP堆栈中(PendSV使用的是MSP)
    BX      LR
	.endasmfunc


	.end
