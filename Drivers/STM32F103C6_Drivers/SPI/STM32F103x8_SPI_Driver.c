/*
 * STM32F103x8_SPI_Driver.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Mohamed Sherif
 */

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8_SPI_Driver.h"

/*******************************************************/

/*******************************************************/
/***************** Generic Variables *******************/
/*******************************************************/
/**
 * index [0] --> SPI1 --> SPI1_Index
 * index [1] --> SPI2 --> SPI2_Index
 */
static SPI_Config_t *Global_SPI_Config[2] = {NULL, NULL};
static SPI_Config_t Global_SPI1_Config;
static SPI_Config_t Global_SPI2_Config;

/*******************************************************/

/*******************************************************/
/***************** Generic Variables *******************/
/*******************************************************/
#define SPI1_Index									0
#define SPI2_Index									1

#define SPI_SR_TXE									(uint8_t)(0x02)                   // Transmit buffer empty
#define SPI_SR_RXNE									(uint8_t)(0x01)                   // Receive buffer NOT empty

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL USART DRIVER" *********/
/*******************************************************/

/**================================================================
 * @Fn           - MCAL_SPI_Init
 * @brief        - Initialization of SPI
 * @param [in]   - SPIx: where x is (1,2)
 * @param [in]   - SPI_config: All configuration for SPI
 * @retval       - None
 * Note          - None
 */
void MCAL_SPI_Init(SPI_Typedef *SPIx, SPI_Config_t* SPI_config){
	uint16_t tmp_CR1 = 0;
	uint16_t tmp_CR2 = 0;

	if(SPIx == SPI1){
		Global_SPI1_Config = *SPI_config;
		Global_SPI_Config[SPI1_Index] = &Global_SPI1_Config;
		RCC_SPI1_CLK_EN();
	}
	else if (SPIx == SPI2){
		Global_SPI2_Config = *SPI_config;
		Global_SPI_Config[SPI2_Index] = &Global_SPI2_Config;
		RCC_SPI2_CLK_EN();
	}

	/* Enable SPI >> Bit 6 SPE: SPI enable */
	tmp_CR1 = (0x1U << 6);

	/* Mode operation Master or Slave */
	tmp_CR1 |= SPI_config->deviceMode;

	/* SPI communication mode */
	tmp_CR1 |= SPI_config->communicationMode;

	/* SPI frame format */
	tmp_CR1 |= SPI_config->frameFormat;

	/* SPI data size */
	tmp_CR1 |= SPI_config->dataSize;

	/* SPI CLK Polarity */
	tmp_CR1 |= SPI_config->CLK_Polarity;

	/* SPI CLK Phase */
	tmp_CR1 |= SPI_config->CLK_Phase;

	/* NSS */
	if(SPI_config->NSS == SPI_NSS_HW_Master_ss_output_Enable){
		tmp_CR2 |= SPI_config->NSS;
	}
	else if(SPI_config->NSS == SPI_NSS_HW_Master_ss_output_Disable){
		tmp_CR2 &= SPI_config->NSS;
	}
	else{
		tmp_CR1 |= SPI_config->NSS;
	}

	/* SPI_Baud rate */
	tmp_CR1 |= SPI_config->CLK_Frequency;

	/* Interrupt */
	if(SPI_config->IRQ_Enable != SPI_IRQ_Enable_NONE){
		tmp_CR2 |= SPI_config->IRQ_Enable;

		if(SPIx == SPI1){
			NVIC_IRQ35_SPI1_ENABLE();
		}
		else if(SPIx == SPI2){
			NVIC_IRQ36_SPI2_ENABLE();
		}
	}

	SPIx->CR1 = tmp_CR1;
	SPIx->CR2 = tmp_CR2;
}

/**================================================================
 * @Fn           - MCAL_SPI_Deinit
 * @brief        - Deinitialization of SPI
 * @param [in]   - SPIx: where x is (1,2)
 * @retval       - None
 * Note          - None
 */
void MCAL_SPI_Deinit(SPI_Typedef *SPIx){
	if(SPIx == SPI1){
		NVIC_IRQ35_SPI1_DISABLE();
		RCC_SPI1_CLK_RST();
	}else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_DISABLE();
		RCC_SPI2_CLK_RST();
	}
}

/**================================================================
 * @Fn           - MCAL_SPI_SendData
 * @brief        - Send buffer through SPI
 * @param [in]   - SPIx: where x is (1,2)
 * @param [in]   - TxBuffer
 * @param [in]   - Polling enable or not
 * @retval       - None
 * Note          - None
 */
void MCAL_SPI_SendData(SPI_Typedef *SPIx, uint16_t *TX_Buffer, enum Polling_Mech pollingEN){
	if(pollingEN == Enable)
		while(!(SPIx->SR & SPI_SR_TXE));

	SPIx->DR = *TX_Buffer;
}

/**================================================================
 * @Fn           - MCAL_SPI_ReceiveData
 * @brief        - Receive data
 * @param [in]   - SPIx: where x is (1,2)
 * @param [in]   - RxBuffer
 * @param [in]   - Polling enable or not
 * @retval       - None
 * Note          - None
 */
void MCAL_SPI_ReceiveData(SPI_Typedef *SPIx, uint16_t *RX_Buffer, enum Polling_Mech pollingEN){
	if(pollingEN == Enable)
			while(!(SPIx->SR & SPI_SR_RXNE));

	*RX_Buffer = SPIx->DR;
}

/**================================================================
 * @Fn           - MCAL_SPI_TX_RX
 * @brief        - Receive  and Transmit data
 * @param [in]   - SPIx: where x is (1,2)
 * @param [in]   - TxBuffer
 * @param [in]   - Polling enable or not
 * @retval       - None
 * Note          - None
 */
void MCAL_SPI_TX_RX(SPI_Typedef *SPIx, uint16_t *TX_Buffer, enum Polling_Mech pollingEN){
	if(pollingEN == Enable)
		while(!(SPIx->SR & SPI_SR_TXE));
	SPIx->DR = *TX_Buffer;

	if(pollingEN == Enable)
		while(!(SPIx->SR & SPI_SR_RXNE));
	*TX_Buffer = SPIx->DR;
}

/**================================================================
 * @Fn           - MCAL_SPI_GPIO_SET_PINs
 * @brief        - Initialization GPIO pins
 * @param [in]   - SPIx: where x is (1,2)
 * Note          - None
 */
void MCAL_SPI_GPIO_SET_PINs(SPI_Typedef *SPIx){
	GPIO_PinConfig_t PinCFG;

	if(SPIx == SPI1)
	{
		//   For SPI1
		// PA4 <<>> NSS
		// PA5 <<>> SCK
		// PA6 <<>> MISO
		// PA7 <<>> MOSI

		if(Global_SPI_Config[SPI1_Index]->deviceMode == SPI_Device_Mode_Master)
		{
			// PA4 <<>> NSS
			switch(Global_SPI_Config[SPI1_Index]->NSS){
				case SPI_NSS_HW_Master_ss_output_Disable:
					PinCFG.pinNumber = GPIO_PIN_4;
					PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
					MCAL_GPIO_Init(GPIOA, &PinCFG);
					break;

				case SPI_NSS_HW_Master_ss_output_Enable:
					PinCFG.pinNumber = GPIO_PIN_4;
					PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
					PinCFG.outputSpeed = GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOA, &PinCFG);
					break;
			}

			// PA5 <<>> SCK
			PinCFG.pinNumber = GPIO_PIN_5;
			PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.outputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			// PA6 <<>> MISO >> full duplex.
			PinCFG.pinNumber = GPIO_PIN_6;
			PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			// PA7 <<>> MOSI
			PinCFG.pinNumber = GPIO_PIN_7;
			PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.outputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

		}
		else
		{
			if(Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HW_Slave){
				PinCFG.pinNumber = GPIO_PIN_4;
				PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOA, &PinCFG);
			}

			//PA5 <<>> SCK
			PinCFG.pinNumber = GPIO_PIN_5;
			PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			// PA6 <<>> MISO
			PinCFG.pinNumber = GPIO_PIN_6;
			PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.outputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			// PA7 <<>> MOSI
			PinCFG.pinNumber = GPIO_PIN_7;
			PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

		}

	}
	else if (SPIx == SPI2)
	{
		//   For SPI2
		// PB12 <<>> NSS
		// PB13 <<>> SCK
		// PB14 <<>> MISO
		// PB15 <<>> MOSI

		if(Global_SPI_Config[SPI2_Index]->deviceMode == SPI_Device_Mode_Master)
		{
			//PB12 <<>> NSS
			switch(Global_SPI_Config[SPI2_Index]->NSS){
			case SPI_NSS_HW_Master_ss_output_Disable:
				PinCFG.pinNumber = GPIO_PIN_12;
				PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOB, &PinCFG);
				break;

			case SPI_NSS_HW_Master_ss_output_Enable:
				PinCFG.pinNumber = GPIO_PIN_12;
				PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
				PinCFG.outputSpeed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCFG);
				break;
			}

			// PB13 <<>> SCK
			PinCFG.pinNumber = GPIO_PIN_13;
			PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.outputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			// PB14 <<>> MISO >> full duplex.
			PinCFG.pinNumber = GPIO_PIN_14;
			PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			// PB15 <<>> MOSI
			PinCFG.pinNumber = GPIO_PIN_15;
			PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.outputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCFG);


		}else
		{
			if(Global_SPI_Config[SPI2_Index]->NSS == SPI_NSS_HW_Slave){
				PinCFG.pinNumber = GPIO_PIN_12;
				PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOB, &PinCFG);
			}

			//PA5 <<>> SCK
			PinCFG.pinNumber = GPIO_PIN_13;
			PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			// PA6 <<>> MISO
			PinCFG.pinNumber = GPIO_PIN_14;
			PinCFG.mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.outputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			// PA7 <<>> MOSI
			PinCFG.pinNumber = GPIO_PIN_15;
			PinCFG.mode = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

		}
	}
}

/*******************************************************/

/*******************************************************/
/****************** ISR Functions **********************/
/*******************************************************/

void SPI1_IRQHandler(void){
	struct S_IRQ_SRC irq_SCR;

	irq_SCR.TXE  = ((SPI1->SR & (1<<1)) >> 1);
	irq_SCR.RXNE = ((SPI1->SR & (1<<0)) >> 0);
	irq_SCR.ERRI = ((SPI1->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI1_Index]->P_IRQ_Callback(irq_SCR);
}

void SPI2_IRQHandler(void){
	struct S_IRQ_SRC irq_SCR;

	irq_SCR.TXE  = ((SPI2->SR & (1<<1)) >> 1);
	irq_SCR.RXNE = ((SPI2->SR & (1<<0)) >> 0);
	irq_SCR.ERRI = ((SPI2->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI2_Index]->P_IRQ_Callback(irq_SCR);
}

/*******************************************************/
