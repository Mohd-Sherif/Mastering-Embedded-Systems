/*
 * STM32F103x8_GPIO_Driver.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Mohamed Sherif
 */

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8_GPIO_Driver.h"

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL GPIO DRIVER" **********/
/*******************************************************/

/**================================================================
 * @Fn				-Get_CRLH_Position
 * @brief 			-gets the pin position in CRL/CRH register
 * @param [in] 		-PinNumber
 * @retval 			-PinPos
 * Note				-None
 */
static uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	uint8_t PinPos = 0;
	switch (PinNumber){
		case GPIO_PIN_0:
		case GPIO_PIN_8:
			PinPos = 0;
			break;
		case GPIO_PIN_1:
		case GPIO_PIN_9:
			PinPos = 4;
			break;
		case GPIO_PIN_2:
		case GPIO_PIN_10:
			PinPos = 8;
			break;
		case GPIO_PIN_3:
		case GPIO_PIN_11:
			PinPos = 12;
			break;
		case GPIO_PIN_4:
		case GPIO_PIN_12:
			PinPos = 16;
			break;
		case GPIO_PIN_5:
		case GPIO_PIN_13:
			PinPos = 20;
			break;
		case GPIO_PIN_6:
		case GPIO_PIN_14:
			PinPos = 24;
			break;
		case GPIO_PIN_7:
		case GPIO_PIN_15:
			PinPos = 28;
			break;
		default :
			/* Do nothing */
			break;
	}
	return PinPos;
}

/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-Initializes the GPIOx PINy periphral according to the specified parameters in the PinConfiguration
 * @param [in] 		-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 		-PinConfig pointer to a GPIO_PinConfig_t structure that contains the configuration information for the specified GPIO peripheral
 * @retval 			-None
 * Note				-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules But LQFP48 Package has only GPIO A,B,Part of C,D exported as external PINS from the MCU
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig){
	/**
	 * Port configuration register low (GPIOx_CRL) Configure PINS from 0 >> 7
	 * Port configuration register high (GPIOx_CRH) Configure PINS from 8 >> 15
	 */
	volatile uint32_t *ConfigRegister = (PinConfig->pinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH;
	uint8_t pin_config = 0;

	/* clear CNFx[1:0] MODEx[1:0] [4 bits] */
	*ConfigRegister &= ~(0xf << Get_CRLH_Position(PinConfig->pinNumber));

	/* check if output mode */
	if(
			(PinConfig->mode == GPIO_MODE_OUTPUT_PP)	||
			(PinConfig->mode == GPIO_MODE_OUTPUT_OD)	||
			(PinConfig->mode == GPIO_MODE_OUTPUT_AF_PP)	||
			(PinConfig->mode == GPIO_MODE_OUTPUT_AF_OD)
		){
			pin_config = ( (( (PinConfig->mode - 4) << 2 ) | (PinConfig->outputSpeed)) & 0x0f);
		}
	else{
		if(
				(PinConfig->mode == GPIO_MODE_ANALOG)			||
				(PinConfig->mode == GPIO_MODE_INPUT_FLOATING)
			){
			pin_config = ( ((PinConfig->mode) << 2) & 0x0f);
		}
		else if(PinConfig->mode == GPIO_MODE_AF_INPUT){ /* considered as floating input */
			pin_config = ( (GPIO_MODE_INPUT_FLOATING << 2) & 0x0f);
		}
		else{
			pin_config = ( (GPIO_MODE_INPUT_PU << 2) & 0x0f);
			//to select between PullUp and PullDown modes
			if(PinConfig->mode == GPIO_MODE_INPUT_PU){
				/* Table 20. Port bit configuration table : PxODR -> 0 */
				GPIOx->ODR |= (PinConfig->pinNumber);
			}
			else{
				/* Table 20. Port bit configuration table : PxODR -> 1 */
				GPIOx->ODR &= ~(PinConfig->pinNumber);
			}
		}
	}
	/* write on CRL or CRH */
	*ConfigRegister |= ((pin_config) << Get_CRLH_Position(PinConfig->pinNumber));
}

/**================================================================
 * @Fn				-MCAL_GPIO_DeInit
 * @brief 			-Reset all GPIO Registers
 * @param [in] 		-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval 			-None
 * Note				-None
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx){
	if (GPIOx == GPIOA){
		RCC->APB2RSTR |=  (1 << 2) ;  /* Bit 2 IOPARST: IO port A reset */
		RCC->APB2RSTR &= ~(1 << 2) ;
	}
	else if (GPIOx == GPIOB){
		RCC->APB2RSTR |=  (1 << 3) ;  /* Bit 3 IOPBRST: IO port B reset */
		RCC->APB2RSTR &= ~(1 << 3) ;
	}
	else if (GPIOx == GPIOC){
		RCC->APB2RSTR |=  (1 << 4) ;  /* Bit 4 IOPCRST: IO port C reset */
		RCC->APB2RSTR &= ~(1 << 4) ;
	}
	else if (GPIOx == GPIOD){
		RCC->APB2RSTR |=  (1 << 5) ;  /* Bit 5 IOPDRST: IO port D reset */
		RCC->APB2RSTR &= ~(1 << 5) ;
	}
	else{
		RCC->APB2RSTR |=  (1 << 6) ;  /* Bit 6 IOPERST: IO port E reset */
		RCC->APB2RSTR &= ~(1 << 6) ;
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_ReadPin
 * @brief 			-Read Specific Pin
 * @param [in] 		-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in]		-PinNumber: Set Pin number According to @ref GPIO_PIN_define
 * @retval 			-the input pin value (two values based on @ref GPIO_PIN_state)
 * Note				-None
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber){
	return (GPIOx->IDR & PinNumber) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

/**================================================================
 * @Fn				-MCAL_GPIO_ReadPort
 * @brief 			-Read Input Port Value
 * @param [in] 		-GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval 			-the input port value
 * Note				-None
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx){
	return GPIOx->IDR;
}

/**================================================================
 * @Fn				-MCAL_GPIO_WritePin
 * @brief 			-Write Specific Pin
 * @param [in] 		-GPIOx: Where x can be (A..G depending on device used) to select the GPIO peripheral
 * @param [in]		-PinNumber: specifies the port bit to read. Set By @ref GPIO_PIN_define
 * @param [in]		-value: value to be written on the pin
 * @retval 			-None
 * Note				-None
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t value){
	/* We can use ODR and Also we can use BSRR to reset and BRR to set pin value */
	if(value == (uint8_t)GPIO_PIN_SET){
		/*  Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
	These bits are write-only and can be accessed in Word mode only.
	0: No action on the corresponding ODRx bit
	1: Set the corresponding ODRx bit              */
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else{
		/*	Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
	These bits are write-only and can be accessed in Word mode only.
	0: No action on the corresponding ODRx bit
	1: Reset the corresponding ODRx bit				*/
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_WritePort
 * @brief 			-Write Output Port Value
 * @param [in] 		-GPIOx: Where x can be (A..G depending on device used) to select the GPIO peripheral
 * @param [in]		-value: value to be written on the port
 * @retval 			-None
 * Note				-None
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t value){
	GPIOx->ODR = value;
}

/**================================================================
 * @Fn				-MCAL_GPIO_TogglePin
 * @brief 			-Toggle The Specified GPIO pin
 * @param [in] 		-GPIOx: Where x can be (A..G depending on device used) to select the GPIO peripheral
 * @param [in]		-PinNumber: specifies the port bit to read. Set By @ref GPIO_PINS_define
 * @retval 			-None
 * Note				-None
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber){
	GPIOx->ODR ^= (uint32_t)PinNumber;
}

/**================================================================
 * @Fn				-MCAL_GPIO_LockPin
 * @brief 			-The Locking Mechanism allows the IO configuration to be Frozen
 * @param [in] 		-GPIOx: Where x can be (A..G depending on device used) to select the GPIO peripheral
 * @param [in]		-PinNumber: specifies the port bit to read. Set By @ref GPIO_PIN_define
 * @retval 			-Ok if piN Config is locked Or Error if pin is not locked (OK and ERROR are define @ref GPIO_LOCK_state)
 * Note				-None
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber){
	uint32_t lock = 1 << 16;
	lock |= (uint32_t)PinNumber;
	/**
	 * LOCK key writing sequence:
	 * Write 1
	 * Write 0
	 * Write 1
	 * Read 0
	 * Read 1 (this read is optional but confirms that the lock is active)
	 */
	GPIOx->LCKR = lock;
	GPIOx->LCKR = PinNumber;
	GPIOx->LCKR = lock;
	lock = GPIOx->LCKR;
	return (GPIOx->LCKR & (1 << 16)) ? GPIO_LOCK_ENABLED : GPIO_LOCK_ERROR;
}

/*******************************************************/
