/*
 * STM32F103x8.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Mohamed Sherif
 */

#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include <stdlib.h>
#include <stdint.h>

/*******************************************************/

/*******************************************************/
/************ Base addresses for Memories **************/
/*******************************************************/
#define FLASH_MEMORY_BASE_ADDRESS					0x08000000UL
#define SYSTEM_MEMORY_BASE_ADDRESS					0x1FFFF000UL
#define SRAM_BASE_ADDRESS							0x20000000UL
#define PERIPHERALS_BASE_ADDRESS					0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE_ADDRESS	0xE0000000UL

/*******************************************************/

/*******************************************************/
/******** Base addresses for BUS Peripherals ***********/
/*******************************************************/

/******** Base addresses for AHB Peripherals ***********/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: RCC                                     */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define RCC_BASE_ADDRESS							0x40021000UL
//#define RCC_BASE_ADDRESS							(PERIPHERALS_BASE_ADDRESS + 0x21000)

/******** Base addresses for APB1 Peripherals **********/

/******** Base addresses for APB2 Peripherals **********/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: GPIO                                    */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/* A & B fully included in LQFP48 package */
#define GPIOA_BASE_ADDRESS							0x40010800UL
#define GPIOB_BASE_ADDRESS							0x40010C00UL

/* C & D partial included in LQFP48 package */
#define GPIOC_BASE_ADDRESS							0x40011000UL
#define GPIOD_BASE_ADDRESS							0x40011400UL

/* E not included in LQFP48 package */
#define GPIOE_BASE_ADDRESS							0x40011800UL

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: AFIO                                    */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define AFIO_BASE_ADDRESS							0x40010000UL

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: EXTI                                    */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define EXTI_BASE_ADDRESS							0x40010400UL

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral register: RCC                            */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
} RCC_TypeDef;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral register: GPIO                           */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} GPIO_TypeDef;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral register: AFIO                           */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;
} AFIO_TypeDef;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral Instants:                                */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define RCC											((RCC_TypeDef *)RCC_BASE_ADDRESS)

#define GPIOA										((GPIO_TypeDef *)GPIOA_BASE_ADDRESS)
#define GPIOB										((GPIO_TypeDef *)GPIOB_BASE_ADDRESS)
#define GPIOC										((GPIO_TypeDef *)GPIOC_BASE_ADDRESS)
#define GPIOD										((GPIO_TypeDef *)GPIOD_BASE_ADDRESS)
#define GPIOE										((GPIO_TypeDef *)GPIOE_BASE_ADDRESS)

#define AFIO										((AFIO_TypeDef *)AFIO_BASE_ADDRESS)

#define EXTI										((EXTI_TypeDef *)EXTI_BASE_ADDRESS)

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* clock enable Macros:                                */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define RCC_AFIO_CLK_EN()							(RCC->APB2ENR |= 1 << 0)

#define RCC_GPIOA_CLK_EN()							(RCC->APB2ENR |= 1 << 2)
#define RCC_GPIOB_CLK_EN()							(RCC->APB2ENR |= 1 << 3)
#define RCC_GPIOC_CLK_EN()							(RCC->APB2ENR |= 1 << 4)
#define RCC_GPIOD_CLK_EN()							(RCC->APB2ENR |= 1 << 5)
#define RCC_GPIOE_CLK_EN()							(RCC->APB2ENR |= 1 << 6)

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Generic Macros:                                     */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*******************************************************/

#endif /* INC_STM32F103X8_H_ */
