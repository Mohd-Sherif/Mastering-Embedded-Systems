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

/***** Base Addresses for SYSTEM BUS Peripherals *******/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: NVIC                                    */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define NVIC_BASE_ADDRESS							0xE000E100UL
#define NVIC_ISER0									(*(volatile uint32_t*)(NVIC_BASE_ADDRESS + 0x00))
#define NVIC_ISER1									(*(volatile uint32_t*)(NVIC_BASE_ADDRESS + 0x04))
#define NVIC_ISER2									(*(volatile uint32_t*)(NVIC_BASE_ADDRESS + 0x08))
#define NVIC_ICER0									(*(volatile uint32_t*)(NVIC_BASE_ADDRESS + 0x80))
#define NVIC_ICER1									(*(volatile uint32_t*)(NVIC_BASE_ADDRESS + 0x84))
#define NVIC_ICER2									(*(volatile uint32_t*)(NVIC_BASE_ADDRESS + 0x88))

/******** Base addresses for AHB Peripherals ***********/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: RCC                                     */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define RCC_BASE_ADDRESS							0x40021000UL
//#define RCC_BASE_ADDRESS							(PERIPHERALS_BASE_ADDRESS + 0x21000)

/******** Base addresses for APB1 Peripherals **********/
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: USART                                   */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define USART2_BASE_ADDRESS							0x40004400UL
#define USART3_BASE_ADDRESS							0x40004800UL

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

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral: USART                                   */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define USART1_BASE_ADDRESS							0x40013800UL

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
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;
} AFIO_TypeDef;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral register: EXTI                           */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} EXTI_TypeDef;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Peripheral register: USART                          */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;

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

#define USART1										((USART_TypeDef *)USART1_BASE_ADDRESS)
#define USART2										((USART_TypeDef *)USART2_BASE_ADDRESS)
#define USART3										((USART_TypeDef *)USART3_BASE_ADDRESS)

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

#define RCC_USART1_CLK_EN()							(RCC->APB2ENR |= 1 << 14)
#define RCC_USART2_CLK_EN()							(RCC->APB1ENR |= 1 << 17)
#define RCC_USART3_CLK_EN()							(RCC->APB1ENR |= 1 << 18)

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* clock disable Macros:                               */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define RCC_USART1_CLK_RST()							(RCC->APB2RSTR |= 1 << 14)
#define RCC_USART2_CLK_RST()							(RCC->APB1RSTR |= 1 << 17)
#define RCC_USART3_CLK_RST()							(RCC->APB1RSTR |= 1 << 18)

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* IVT Macros:                                         */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* EXTI */
#define EXTI0_IRQ									6
#define EXTI1_IRQ									7
#define EXTI2_IRQ									8
#define EXTI3_IRQ									9
#define EXTI4_IRQ									10
#define EXTI5_IRQ									23
#define EXTI6_IRQ									23
#define EXTI7_IRQ									23
#define EXTI8_IRQ									23
#define EXTI9_IRQ									23
#define EXTI10_IRQ									40
#define EXTI11_IRQ									40
#define EXTI12_IRQ									40
#define EXTI13_IRQ									40
#define EXTI14_IRQ									40
#define EXTI15_IRQ									40

/* USART */
#define USART1_IRQ									37
#define USART2_IRQ									38
#define USART3_IRQ									39

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* NVIC IRQ Enable Macros:                             */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* EXTI */
#define NVIC_IRQ6_EXTI0_ENABLE()					(NVIC_ISER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_ENABLE()					(NVIC_ISER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_ENABLE()					(NVIC_ISER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_ENABLE()					(NVIC_ISER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_ENABLE()					(NVIC_ISER0 |= 1 << 10)
#define NVIC_IRQ23_EXTI5_9_ENABLE()					(NVIC_ISER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI10_15_ENABLE()				(NVIC_ISER1 |= 1 << 8)  /* 40 - 32 = 8 */

/* USART */
#define NVIC_IRQ37_USART1_ENABLE()					(NVIC_ISER1 |= 1 << 5) /* 37 - 32 = 5 */
#define NVIC_IRQ38_USART2_ENABLE()					(NVIC_ISER1 |= 1 << 6) /* 38 - 32 = 6 */
#define NVIC_IRQ39_USART3_ENABLE()					(NVIC_ISER1 |= 1 << 7) /* 39 - 32 = 7 */

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* NVIC IRQ Disable Macros:                            */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* EXTI */
#define NVIC_IRQ6_EXTI0_DISABLE()					(NVIC_ICER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_DISABLE()					(NVIC_ICER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_DISABLE()					(NVIC_ICER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_DISABLE()					(NVIC_ICER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_DISABLE()					(NVIC_ICER0 |= 1 << 10)
#define NVIC_IRQ23_EXTI5_9_DISABLE()				(NVIC_ICER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI10_15_DISABLE()				(NVIC_ICER1 |= 1 << 8)  /* 40 - 32 = 8 */

/* USART */
#define NVIC_IRQ37_USART1_DISABLE()					(NVIC_ICER1 |= 1 << 5) /* 37 - 32 = 5 */
#define NVIC_IRQ38_USART2_DISABLE()					(NVIC_ICER1 |= 1 << 6) /* 38 - 32 = 6 */
#define NVIC_IRQ39_USART3_DISABLE()					(NVIC_ICER1 |= 1 << 7) /* 39 - 32 = 7 */

/*******************************************************/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Generic Macros:                                     */
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/*******************************************************/

#endif /* INC_STM32F103X8_H_ */
