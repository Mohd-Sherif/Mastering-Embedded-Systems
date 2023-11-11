/*
 * STM32F103x8_RCC_Driver.h
 *
 *  Created on: Nov 11, 2023
 *      Author: Mohamed Sherif
 */

#ifndef INC_STM32F103X8_RCC_DRIVER_H_
#define INC_STM32F103X8_RCC_DRIVER_H_

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8.h"
#include "STM32F103x8_GPIO_Driver.h"

/*******************************************************/

/*******************************************************/
/********* Macros Configuration References *************/
/*******************************************************/
#define HSE_CLOCK 			(uint32_t)16000000UL
#define HSI_RC_CLOCK 		(uint32_t)8000000UL

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL GPIO DRIVER" **********/
/*******************************************************/
uint32_t MCAL_RCC_GetSYSCLKFreq(void); /* get SYSCLK bus Frequency */

uint32_t MCAL_RCC_GetHCLKFreq(void); /* get AHB bus Frequency */
uint32_t MCAL_RCC_GetPCLK1Freq(void); /* get APB1 bus Frequency */
uint32_t MCAL_RCC_GetPCLK2Freq(void); /* get APB2 bus Frequency */

/*******************************************************/

#endif /* INC_STM32F103X8_RCC_DRIVER_H_ */
