/*
 * STM32F103x8_USART_Driver.h
 *
 *  Created on: Nov 11, 2023
 *      Author: Mohamed Sherif
 */

#ifndef INC_STM32F103X8_USART_DRIVER_H_
#define INC_STM32F103X8_USART_DRIVER_H_

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8.h"
#include "STM32F103x8_GPIO_Driver.h"
#include "STM32F103x8_RCC_Driver.h"

/*******************************************************/

/*******************************************************/
/******** User type definitions (structures) ***********/
/*******************************************************/

typedef struct{
	/**
	 * @mode
	 * Specifies Tx/Rx Enable/Disable.
	 * this parameter must be set based on @ref USART_Mode_define.
	 */
	uint8_t mode;

	/**
	 * @baudRate
	 * Specifies USART Communication Baud Rate.
	 * this parameter must be set based on @ref USART_BaudRate_define.
	 */
	uint32_t baudRate;

	/**
	 * @payloadLength
	 * Specifies number of data bits transmitted or received in a frame.
	 * this parameter must be set based on @ref USART_PayloadLength_define.
	 */
	uint8_t payloadLength;

	/**
	 * @parity
	 * Specifies the parity mode.
	 * this parameter must be set based on @ref USART_Parity_define.
	 */
	uint8_t parity;

	/**
	 * @stopBits
	 * Specifies number of stop bits in a frame.
	 * this parameter must be set based on @ref USART_StopBits_define.
	 */
	uint8_t stopBits;

	/**
	 * @HW_FlowCtl
	 * Specifies whether the hardware flow control mode is enabled or disabled.
	 * this parameter must be set based on @ref USART_HwFlowCtl_define.
	 */
	uint8_t HW_FlowCtl;

	/**
	 * @IRQ_EN
	 * Enable or Disable IRQ Tx/Rx.
	 * this parameter must be set based on @ref USART_IRQ_define.
	 */
	uint8_t IRQ_EN;

	/**
	 * @P_IRQ_CallBack
	 * Set the C Function() which will be called once the IRQ Happen.
	 */
	void(* P_IRQ_CallBack)(void);
}USART_Config_t;

/*******************************************************/

/*******************************************************/
/********* Macros Configuration References *************/
/*******************************************************/
/* @ref USART_Mode_define */
#define USART_Mode_Tx					(1 << 3)			/* Bit 3 TE: Transmitter enable */
#define USART_Mode_Rx					(1 << 2)			/* Bit 2 RE: Receiver enable */
#define USART_Mode_Tx_Rx				(1 << 3 | 1 << 2)	/* Bit 3 TE: Transmitter enable -- Bit 2 RE: Receiver enable */

/* @ref USART_BaudRate_define */
#define USART_BaudRate_2400				((uint32_t)(2400))
#define USART_BaudRate_9600				((uint32_t)(9600))
#define USART_BaudRate_19200			((uint32_t)(19200))
#define USART_BaudRate_57600			((uint32_t)(57600))
#define USART_BaudRate_115200			((uint32_t)(115200))
#define USART_BaudRate_230400			((uint32_t)(230400))
#define USART_BaudRate_460800			((uint32_t)(460800))
#define USART_BaudRate_921600			((uint32_t)(921600))
#define USART_BaudRate_2250000			((uint32_t)(2250000))
#define USART_BaudRate_4500000			((uint32_t)(4500000))

/* @ref USART_PayloadLength_define */
#define USART_PayloadLength_8B			((uint32_t)(0 << 12))
#define USART_PayloadLength_9B			((uint32_t)(1 << 12))

/* @ref USART_Parity_define */
#define USART_Parity_NONE				((uint32_t)(0 << 10))
#define USART_Parity_EVEN				((uint32_t)(1 << 10))
#define USART_Parity_ODD				((uint32_t)(1 << 10 | 1 << 9))

/* @ref USART_StopBits_define */
#define USART_StopBits_1				((uint32_t)(0 << 12))
#define USART_StopBits_Half				((uint32_t)(1 << 12))
#define USART_StopBits_2				((uint32_t)(2 << 12))
#define USART_StopBits_1_Half			((uint32_t)(3 << 12))

/* @ref USART_HwFlowCtl_define */
#define USART_HwFlowCtl_NONE			((uint32_t)(0))
#define USART_HwFlowCtl_RTS				((uint32_t)(1 << 8))
#define USART_HwFlowCtl_CTS				((uint32_t)(1 << 9))
#define USART_HwFlowCtl_RTS_CTS			((uint32_t)(1 << 9 | 1 << 8))

/* @ref USART_IRQ_define */
#define USART_IRQ_NONE					((uint32_t)(0))
#define USART_IRQ_TXE					((uint32_t)(1<<7))
#define USART_IRQ_TC					((uint32_t)(1<<6))
#define USART_IRQ_RXNE					((uint32_t)(1<<5))
#define USART_IRQ_PE					((uint32_t)(1<<8))

enum Polling_mechanism{
	enable,
	disable
};

/* BaudRate Calculation */
/**
 * USARTDIV = fclk / (16 * Baudrate)
 * USARTDIV_MUL100 = (uint32)(100 * fclk ) / (16 * Baudrate) == (25 * fclk) / (4 * Baudrate)
 * DIV_Mantissa_MUL100 = Integer Part (USARTDIV ) * 100
 * DIV_Mantissa = Integer Part (USARTDIV )
 * DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100)* 16 ) / 100
 */
#define USARTDIV(_PCLK_, _BAUD_)			((uint32_t)(_PCLK_/(16 * _BAUD_)))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)		((uint32_t)((25 * _PCLK_) / (4 * _BAUD_)))
#define Mantissa_MUL100(_PCLK_, _BAUD_)		((uint32_t)(USARTDIV(_PCLK_, _BAUD_) * 100))
#define Mantissa(_PCLK_, _BAUD_)			((uint32_t)(USARTDIV(_PCLK_, _BAUD_)))
#define DIV_Fraction(_PCLK_, _BAUD_)		((uint32_t)((((USARTDIV_MUL100(_PCLK_, _BAUD_)) - (Mantissa_MUL100(_PCLK_, _BAUD_))) * 16) / 100) )
#define USART_BRR_REGISTER(_PCLK_, _BAUD_)	( (Mantissa(_PCLK_, _BAUD_) << 4 ) | (DIV_Fraction(_PCLK_, _BAUD_) & 0xF) )

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL USART DRIVER" *********/
/*******************************************************/

void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config_t *USART_Config);
void MCAL_USART_DeInit(USART_TypeDef *USARTx);

void MCAL_USART_GPIO_Set_Pins(USART_TypeDef *USARTx);

void MCAL_USART_SendData(USART_TypeDef *USARTx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn);
void MCAL_USART_ReceiveData(USART_TypeDef *USARTx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn);

void MCAL_USART_Wait_Tc(USART_TypeDef *USARTx);

/*******************************************************/

#endif /* INC_STM32F103X8_USART_DRIVER_H_ */
