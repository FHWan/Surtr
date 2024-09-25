#include "explore_system.h"

/**
 * @Description 执行汇编WFI(Wait for interrupt)指令
 */
__asm void WFI_SET(void)
{
	WFI;
}

/**
 * @Description 关闭所有中断(但是不包括fault和NMI中断)
 */
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR
}

/**
 * @Description 开启所有中断
 */
__asm void INTX_ENABLE(void)
{
	CPSIE	I
	BX	LR
}

/**
 * @Description 开启所有中断
 * @param addr 栈顶地址
 */
__asm void MSR_MSP(u32 addr)
{
	MSR	MSP,	r0
	BX	r14
}
