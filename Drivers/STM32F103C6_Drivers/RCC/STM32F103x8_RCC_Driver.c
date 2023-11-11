/*
 * STM32F103x8_RCC_Driver.c
 *
 *  Created on: Nov 11, 2023
 *      Author: Mohamed Sherif
 */

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8_RCC_Driver.h"

/*******************************************************/

/*******************************************************/
/***************** Generic Variables *******************/
/*******************************************************/
/*Bits 7:4 HPRE: AHB prescaler
Set and cleared by software to control the division factor of the AHB clock.
0xxx: SYSCLK not divided
(8)1000: SYSCLK divided by 2
(9)1001: SYSCLK divided by 4
(10)1010: SYSCLK divided by 8
(11)1011: SYSCLK divided by 16
(12)1100: SYSCLK divided by 64
(13)1101: SYSCLK divided by 128
(14)1110: SYSCLK divided by 256
(15)1111: SYSCLK divided by 512   */
const uint8_t AHB_PrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9}; /* each shift 1 right = divide by 2 */


/* Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB low-speed clock
(PCLK1).
Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16 */
const uint8_t APB_PrescTable[8U] = {0, 0, 0, 0, 1, 2, 3, 4}; /* each shift 1 right = divide by 2 */

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL EXTI DRIVER" **********/
/*******************************************************/

/**===============================================================================================
 * @FName			- MCAL_RCC_GetSYSCLKFreq
 * @Brief 			- get SYSCLK bus Frequency
 * @Return Value	- SYSCLK bus Frequency
 * @Note			- This function does not support fully functionality
 * 					  where it works only assuming that the clock source
 * 					  for the system is HSI source (its functionality can be improved later)
 */
uint32_t MCAL_RCC_GetSYSCLKFreq(void){
	uint32_t sysClkFreq;
	/*Bits 3:2 SWS: System clock switch status
	Set and cleared by hardware to indicate which clock source is used as system clock.
	00: HSI oscillator used as system clock
	01: HSE oscillator used as system clock
	10: PLL used as system clock
	11: not applicable*/
	switch( ( (RCC->CFGR >> 2) & 0b11 ) ){
		case 0b00:
			sysClkFreq = HSI_RC_CLOCK;
			break;
		case 0b01:
			/* TODO: you need to calculate it //HSE user should specify it */
			sysClkFreq = HSE_CLOCK;
			break;
		case 0b10:
			/* TODO: you need to calculate it PLLCLK & PLLMUL & PLL Source MUX user should specify it */
			/* this needs calculations */
			sysClkFreq = 16000000;
			break;
		default: /* Do Nothing */ break;
	}
	return sysClkFreq;
}

/**===============================================================================================
 * @FName			- MCAL_RCC_GetHCLKFreq
 * @Brief 			- get AHB bus Frequency
 * @Return Value	- AHB bus Frequency
 */
uint32_t MCAL_RCC_GetHCLKFreq(void){
	/* Bits 7:4 HPRE: AHB prescaler */
	return ( MCAL_RCC_GetSYSCLKFreq() >> AHB_PrescTable[ (RCC->CFGR >> 4) & 0xF ] );
}

/**===============================================================================================
 * @FName			- MCAL_RCC_GetPCLK1Freq
 * @Brief 			- get APB1 bus Frequency
 * @Return Value	- APB1 bus Frequency
 */
uint32_t MCAL_RCC_GetPCLK1Freq(void){
	/* Bits 10:8 PPRE1: APB low-speed prescaler (APB1) */
	return ( MCAL_RCC_GetHCLKFreq() >> APB_PrescTable[ (RCC->CFGR >> 8) & 0b111 ] );
}

/**===============================================================================================
 * @FName			- MCAL_RCC_GetPCLK2Freq
 * @Brief 			- get APB2 bus Frequency
 * @Return Value	- APB2 bus Frequency
 */
uint32_t MCAL_RCC_GetPCLK2Freq(void){
	/* Bits 13:11 PPRE2: APB high-speed prescaler (APB2) */
	return ( MCAL_RCC_GetHCLKFreq() >> APB_PrescTable[ (RCC->CFGR >> 11) & 0b111 ] );
}

/*******************************************************/
