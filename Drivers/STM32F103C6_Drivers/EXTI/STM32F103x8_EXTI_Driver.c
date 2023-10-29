/*
 * STM32F103x8_EXTI_Driver.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Mohamed Sherif
 */

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8_EXTI_Driver.h"

/*******************************************************/

/*******************************************************/
/***************** Generic Variables *******************/
/*******************************************************/
void (*GP_IRQ_CallBack[16])(void);

/*******************************************************/

/*******************************************************/
/******************** Generic Macros *******************/
/*******************************************************/
#define AFIO_GPIO_EXTI_Mapping(GPIOx)	(	(GPIOx == GPIOA) ? 0 : \
											(GPIOx == GPIOB) ? 1 : \
											(GPIOx == GPIOC) ? 2 : \
											(GPIOx == GPIOD) ? 3 : 0	)

/*******************************************************/

/*******************************************************/
/******************** Generic Functions ****************/
/*******************************************************/
/**===============================================================================================
 * @FName			- Enable_NVIC
 * @Brief 			- Enables the NVIC corresponding line to the passed line
 * @Parameter [in] 	- IRQ: Interrupt input line number
 * @Return Value	- NONE
 * Note				- NONE
 */
static void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ){
		case 0:
			NVIC_IRQ6_EXTI0_ENABLE();
			break;
		case 1:
			NVIC_IRQ7_EXTI1_ENABLE();
			break;
		case 2:
			NVIC_IRQ8_EXTI2_ENABLE();
			break;
		case 3:
			NVIC_IRQ9_EXTI3_ENABLE();
			break;
		case 4:
			NVIC_IRQ10_EXTI4_ENABLE();
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_ENABLE();
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_ENABLE();
			break;
	}
}

/**===============================================================================================
 * @FName			- Disable_NVIC
 * @Brief 			- Enables the NVIC corresponding line to the passed line
 * @Parameter [in] 	- IRQ: Interrupt input line number
 * @Return Value	- NONE
 * Note				- NONE
 */
void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ){
		case 0:
			NVIC_IRQ6_EXTI0_DISABLE();
			break;
		case 1:
			NVIC_IRQ7_EXTI1_DISABLE();
			break;
		case 2:
			NVIC_IRQ8_EXTI2_DISABLE();
			break;
		case 3:
			NVIC_IRQ9_EXTI3_DISABLE();
			break;
		case 4:
			NVIC_IRQ10_EXTI4_DISABLE();
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_DISABLE();
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_DISABLE();
			break;
	}
}

/**===============================================================================================
 * @FName			- Update_EXTI
 * @Brief 			- Used to initialize/Update EXTI from specific GPIO pin and specify the mask/trigger options and callback function
 * @Parameter [in] 	- EXTI_Config: Pointer takes the address of EXTI_PinConfig_t structure that contains
 * 								 Configuration data for a single EXTI pin
 * @Return Value	- NONE
 * Note				- NONE
 */
static void Update_EXTI(EXTI_PinConfig_t *EXTI_Config){
	/**
	 * 1- Configure GPIO PIN to be AF INPUT [Floating INPUT].
	 */
	GPIO_PinConfig_t gpioPinCfg;
	gpioPinCfg.pinNumber = EXTI_Config->pin.GPIO_Pin;
	gpioPinCfg.mode = GPIO_MODE_AF_INPUT;
	MCAL_GPIO_Init(EXTI_Config->pin.GPIO_Port, &gpioPinCfg);

	/**
	 * 2-Update AFIO to route EXTI line between GPIO_Port A, B, C, D.
	 */
	uint8_t AFIO_EXTICR_Index = EXTI_Config->pin.EXTI_InputLineNumber / 4;
	uint8_t AFIO_EXTICR_Pin_Shift = (EXTI_Config->pin.EXTI_InputLineNumber % 4) * 4;

	/* Clear the four bits first */
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_Pin_Shift);

	/* Choose GPIO_Port to be mapped into EXTI pin */
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ( (AFIO_GPIO_EXTI_Mapping(EXTI_Config->pin.GPIO_Port) & 0x0F) << AFIO_EXTICR_Pin_Shift );

	/**
	 * 3-choose Trigger_Case for EXTI Pin.
	 */

	/* First we clear Trigger selection bits */
	EXTI->RTSR &= ~(1 << EXTI_Config->pin.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->pin.EXTI_InputLineNumber);

	/* Then we choose Trigger_Case */
	switch(EXTI_Config->triggerCase){
		case EXTI_Trigger_RISING:
			EXTI->RTSR |= (1 << EXTI_Config->pin.EXTI_InputLineNumber);
			break;
		case EXTI_Trigger_FALLING:
			EXTI->FTSR |= (1 << EXTI_Config->pin.EXTI_InputLineNumber);
			break;
		case EXTI_Trigger_RISING_OR_FALLING:
			EXTI->RTSR |= (1 << EXTI_Config->pin.EXTI_InputLineNumber);
			EXTI->FTSR |= (1 << EXTI_Config->pin.EXTI_InputLineNumber);
			break;
		default: /* Do Nothing */ break;
	}

	/**
	 * 4-locate Interrupt handle Function called in main if IRQ is done.
	 */
	GP_IRQ_CallBack[EXTI_Config->pin.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

	/**
	 * 5-Enable/Disable IRQ for EXTI Pin.
	 */
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE){
		EXTI->IMR |= (1 << EXTI_Config->pin.EXTI_InputLineNumber);

		/* Enable NVIC IRQ PIN */
		Enable_NVIC(EXTI_Config->pin.EXTI_InputLineNumber);
	}
	else{
		EXTI->IMR &= ~(1 << EXTI_Config->pin.EXTI_InputLineNumber);

		/* Disable NVIC IRQ PIN */
		Disable_NVIC(EXTI_Config->pin.EXTI_InputLineNumber);
	}
}

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL EXTI DRIVER" **********/
/*******************************************************/

/**===============================================================================================
 * @FName			- MCAL_EXTI_GPIO_Init
 * @Brief 			- Used to initialize EXTI from specific GPIO pin and specify the mask/trigger options and callback function
 * @Parameter [in] 	- PinConfig: Pointer takes the address of EXTI_PinConfig_t structure that contains
 * 								 Configuration data for a single EXTI pin
 * @Return Value	- NONE
 * Note				- PinConfig is only set by @ref EXTI_define & @ref EXTI_Trigger_define & @ref EXTI_IRQ_define
 * 					  it is also mandatory to enable RCC clock for AFIO and corresponding GPIO
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *PinConfig){
	Update_EXTI(PinConfig);
}

/**===============================================================================================
 * @FName			- MCAL_EXTI_GPIO_DeInit
 * @Brief 			- Resets all EXTI registers to the reset values and NVIC corresponding IRQ masks
 * @Parameter [in] 	- NONE
 * @Return Value	- NONE
 * Note				- NONE
 */
void MCAL_EXTI_GPIO_DeInit(void){
	/* Clear EXTI registers */
	EXTI->EMR   = 0x00000000;
	EXTI->IMR   = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;

	/* all pins are Write 1 to clear */
	EXTI->PR    = 0xFFFFFFFF;

	/* Disable EXTI IRQ masks from NVIC */
	NVIC_IRQ6_EXTI0_DISABLE()		;
	NVIC_IRQ7_EXTI1_DISABLE()		;
	NVIC_IRQ8_EXTI2_DISABLE()       ;
	NVIC_IRQ9_EXTI3_DISABLE()       ;
	NVIC_IRQ10_EXTI4_DISABLE()      ;
	NVIC_IRQ23_EXTI5_9_DISABLE()    ;
	NVIC_IRQ40_EXTI10_15_DISABLE()	;
}

/**===============================================================================================
 * @FName			- MCAL_EXTI_GPIO_Update
 * @Brief 			- Used to Update EXTI from specific GPIO pin and specify the mask/trigger options and callback function
 * @Parameter [in] 	- PinConfig: Pointer takes the address of EXTI_PinConfig_t structure that contains
 * 								 Configuration data for a single EXTI pin
 * @Return Value	- NONE
 * Note				- PinConfig is only set by @ref EXTI_define & @ref EXTI_Trigger_define & @ref EXTI_IRQ_define
 * 					  it is also mandatory to enable RCC clock for AFIO and corresponding GPIO
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *PinConfig){
	Update_EXTI(PinConfig);
}
