/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef volatile unsigned int vuint32_t;

#define RCC_BASE	0x40021000
#define RCC_APB2ENR	(*(vuint32_t *)(RCC_BASE + 0x18))
#define RCC_CFGR	(*(vuint32_t *)(RCC_BASE + 0x04))
#define RCC_CR		(*(vuint32_t *)(RCC_BASE + 0x00))

#define GPIOA_BASE	0x40010800
#define GPIOA_CRH	(*(vuint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR	(*(vuint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOx_CRL	(*(vuint32_t *)(GPIOA_BASE + 0x00))

#define EXTI_BASE	0x40010400
#define EXTI_RTSR	(*(vuint32_t *)(EXTI_BASE + 0x08))
#define EXTI_IMR	(*(vuint32_t *)(EXTI_BASE + 0x00))
#define EXTI_PR		(*(vuint32_t *)(EXTI_BASE + 0x14))

#define AFIO_BASE		0x40010000
#define AFIO_EXTICR1	(*(vuint32_t *)(AFIO_BASE + 0x08))

#define NVIC_ISER0   (*(vuint32_t *)(0xE000E100))

int main(void)
{
	RCC_APB2ENR |= (1 << 2);
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	/*CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
These bits are written by software to configure the corresponding I/O port.
Refer to Table 20: Port bit configuration table.
In input mode (MODE[1:0]=00):
00: Analog mode
01: Floating input (reset state)
10: Input with pull-up / pull-down
11: Reserved
In output mode (MODE[1:0] > 00):
00: General purpose output push-pull
01: General purpose output Open-drain
10: Alternate function output Push-pull
11: Alternate function output Open-drain*/
	GPIOx_CRL |= 1 << 2; /*set A0 at input mode*/

	/*Bits 15:0 EXTIx[3:0]: EXTI x configuration (x= 0 to 3)
These bits are written by software to select the source input for EXTIx external interrupt.
Refer to Section 10.2.5: External interrupt/event line mapping
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
0101: PF[x] pin
0110: PG[x] pin*/
	AFIO_EXTICR1 |= 0b0000 << 0; /* select A0 input for EXTI0 external interrupt */

	/*Bits 19:0 TRx: Rising trigger event configuration bit of line x
0: Rising trigger disabled (for Event and Interrupt) for input line
1: Rising trigger enabled (for Event and Interrupt) for input line.*/
	EXTI_RTSR |= 1 << 0; /* set rising edge */

	/*Bits 19:0 MRx: Interrupt Mask on line x
0: Interrupt request from Line x is masked
1: Interrupt request from Line x is not masked*/
	EXTI_IMR |= 1 << 0; /* set line 0 unmasked */

	NVIC_ISER0 |=(1<<6);

	while(1);
}

void EXTI0_IRQHandler(){
	GPIOA_ODR ^= (1UL << 13); /* toggle led */

/*Bits 19:0 PRx: Pending bit
0: No trigger request occurred
1: selected trigger request occurred
This bit is set when the selected edge event arrives on the external interrupt line. This bit is
cleared by writing a ‘1’ into the bit. */
	EXTI_PR |= 1 << 0; /* clear interrupt to avoid infinite loop */
}