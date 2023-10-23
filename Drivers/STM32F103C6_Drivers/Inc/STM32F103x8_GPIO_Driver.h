/*
 * STM32F103x8_GPIO_Driver.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Mohamed Sherif
 */

#ifndef INC_STM32F103X8_GPIO_DRIVER_H_
#define INC_STM32F103X8_GPIO_DRIVER_H_

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8.h"

/*******************************************************/

/*******************************************************/
/******** User type definitions (structures) ***********/
/*******************************************************/
/* Configuration Structure */
typedef struct{
	/**
	 * @pinNumber
	 * Specifies the GPIO pins to be configured.
	 * This parameter must be set based on @ref GPIO_PIN_define.
	 */
	uint16_t pinNumber;

	/**
	 * @mode
	 * Specifies the operating mode for the selected pin.
	 * This parameter can be a value of @ref GPIO_MODE_define.
	 */
	uint8_t mode;

	/**
	 * @outputSpeed
	 * Specifies the speed for the selected pin.
	 * This parameter can be a value of @ref GPIO_SPEED_define.
	 */
	uint8_t outputSpeed;
}GPIO_PinConfig_t;

/*******************************************************/

/*******************************************************/
/********* Macros Configuration References *************/
/*******************************************************/
/* @ref GPIO_PIN_define */
#define GPIO_PIN_0					((uint16_t)0x0001)  /*	Pin 0 selected 		*/
#define GPIO_PIN_1					((uint16_t)0x0002)  /*	Pin 1 selected 		*/
#define GPIO_PIN_2					((uint16_t)0x0004)  /*	Pin 2 selected 		*/
#define GPIO_PIN_3					((uint16_t)0x0008)  /*	Pin 3 selected 		*/
#define GPIO_PIN_4					((uint16_t)0x0010)  /*	Pin 4 selected 		*/
#define GPIO_PIN_5					((uint16_t)0x0020)  /*	Pin 5 selected 		*/
#define GPIO_PIN_6					((uint16_t)0x0040)  /*	Pin 6 selected 		*/
#define GPIO_PIN_7					((uint16_t)0x0080)  /*	Pin 7 selected 		*/
#define GPIO_PIN_8					((uint16_t)0x0100)  /*	Pin 8 selected 		*/
#define GPIO_PIN_9					((uint16_t)0x0200)  /*	Pin 9 selected 		*/
#define GPIO_PIN_10					((uint16_t)0x0400)  /*	Pin 10 selected 	*/
#define GPIO_PIN_11					((uint16_t)0x0800)  /*	Pin 11 selected 	*/
#define GPIO_PIN_12					((uint16_t)0x1000)  /*	Pin 12 selected 	*/
#define GPIO_PIN_13					((uint16_t)0x2000)  /*	Pin 13 selected 	*/
#define GPIO_PIN_14					((uint16_t)0x4000)  /*	Pin 14 selected 	*/
#define GPIO_PIN_15					((uint16_t)0x8000)  /*	Pin 15 selected 	*/
#define GPIO_PIN_All				((uint16_t)0xFFFF)  /*	All pins selected 	*/

/* @ref GPIO_MODE_define */
#define GPIO_MODE_ANALOG 					0x00000000U 	/* 0: Analog mode                          */
#define GPIO_MODE_INPUT_FLOATING 			0x00000001U		/* 1: Floating input (reset state)         */
#define GPIO_MODE_INPUT_PU 					0x00000002U		/* 2: Input with pull-up                   */
#define GPIO_MODE_INPUT_PD 					0x00000003U		/* 3: pull-down                            */
#define GPIO_MODE_OUTPUT_PP 				0x00000004U		/* 4: General purpose output push-pull     */
#define GPIO_MODE_OUTPUT_OD 				0x00000005U		/* 5: General purpose output Open-drain    */
#define GPIO_MODE_OUTPUT_AF_PP 				0x00000006U		/* 6: Alternate function output Push-pull  */
#define GPIO_MODE_OUTPUT_AF_OD				0x00000007U		/* 7: Alternate function output Open-drain */
#define GPIO_MODE_AF_INPUT					0x00000008U		/* 8: Alternate function input Open-drain  */

/* @ref GPIO_SPEED_define */
#define GPIO_SPEED_10M					0x00000001U			/* 1: Output mode, max speed 10 MHz. */
#define GPIO_SPEED_2M					0x00000002U			/* 2: Output mode, max speed 2 MHz.  */
#define GPIO_SPEED_50M					0x00000003U	        /* 3: Output mode, max speed 50 MHz. */

/* @ref GPIO_PIN_state */
#define GPIO_PIN_SET					1
#define GPIO_PIN_RESET					0

/* @ref GPIO_LOCK_state */
#define GPIO_LOCK_ENABLED				1
#define GPIO_LOCK_ERROR					0

/*******************************************************/
/******* APIs Supported by "MCAL GPIO DRIVER" **********/
/*******************************************************/
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);

/*******************************************************/

#endif /* INC_STM32F103X8_GPIO_DRIVER_H_ */
