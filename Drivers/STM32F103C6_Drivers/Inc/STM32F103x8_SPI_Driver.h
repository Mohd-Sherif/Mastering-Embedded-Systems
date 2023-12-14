/*
 * STM32F103x8_SPI_Driver.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Mohamed Sherif
 */

#ifndef INC_STM32F103X8_SPI_DRIVER_H_
#define INC_STM32F103X8_SPI_DRIVER_H_

/*******************************************************/
/********************* Includes ************************/
/*******************************************************/
#include "STM32F103x8.h"
#include "STM32F103x8_GPIO_Driver.h"

/*******************************************************/

/*******************************************************/
/******** User type definitions (structures) ***********/
/*******************************************************/
struct S_IRQ_SRC{
	uint8_t TXE     :1; /* TX buffer EMPTY Interrupt. */
	uint8_t RXNE    :1; /* RX buffer NOT EMPTY Interrupt. */
	uint8_t ERRI    :1; /* Error Interrupt. */
	uint8_t Reseved :5;
};

typedef struct{
	/**
	 * @deviceMode
	 * Specify SPI operation mode it is master or slave.
	 * this parameter must be set based on @ref SPI_Device_Mode_define.
	 */
	uint16_t deviceMode;

	/**
	 * @communicationMode
	 * Define SPI direction mode state.
	 * this parameter must be set based on @ref SPI_Communication_Mode_define.
	 */
	uint16_t communicationMode;

	/**
	 * @frameFormat
	 * Specify MSB or LSB.
	 * this parameter must be set based on @ref SPI_Frame_Format_define.
	 */
	uint16_t frameFormat;

	/**
	 * @dataSize
	 * Specify data size.
	 * this parameter must be set based on @ref SPI_Data_Size_define.
	 */
	uint16_t dataSize;

	/**
	 * @CLK_Polarity
	 * Specify clock polarity.
	 * this parameter must be set based on @ref SPI_CLK_Polarity_define.
	 */
	uint16_t CLK_Polarity;

	/**
	 * @CLK_Phase
	 * Specify clock phase.
	 * this parameter must be set based on @ref SPI_CLK_Phase_define.
	 */
	uint16_t CLK_Phase;

	/**
	 * @NSS
	 * Specify if NSS signal is managed by H.W (NSS pin) or S.W (SSI bit Enable or Disable).
	 * this parameter must be set based on @ref SPI_NSS_define.
	 */
	uint16_t NSS;

	/**
	 * @CLK_Frequency
	 * Specify the baud rate prescaler value which configure transmit or receive SCK clock.
	 * this parameter must be set based on @ref SPI_CLK_Frequency_define.
	 */
	uint16_t CLK_Frequency;

	/**
	 * @IRQ_Enable
	 * Enable/Disable Interrupt.
	 * this parameter must be set based on @ref SPI_IRQ_Enable_define.
	 */
	uint16_t IRQ_Enable;

	/**
	 * @P_IRQ_Callback
	 * Set the C Function() which will be called once the IRQ Happen.
	 */
	void (* P_IRQ_Callback) (struct S_IRQ_SRC irq_SCR);
} SPI_Config_t;

/*******************************************************/

/*******************************************************/
/********* Macros Configuration References *************/
/*******************************************************/
/* @ref SPI_Device_Mode_define */
#define SPI_Device_Mode_Slave                     (0x00000000UL)              //CR1.MSTR <<>> Slave configuration
#define SPI_Device_Mode_Master                    (0x1U << 2)                 //CR1.MSTR <<>> Master configuration

/* @ref SPI_Communication_Mode_define */
#define SPI_Direction_2Lines                      (0x00000000UL)
#define SPI_Direction_2Lines_RX_Only              (0x1U << 10)                // Bit 10 RXONLY: Receive only
#define SPI_Direction_1Lines_RX_Only              (0x1U << 15)                // Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_Direction_1Lines_TX_Only              (0x1U << 15) | (0x1U << 14) // Bit 15 BIDIMODE: Bidirectional data mode enable & Bit 14 BIDIOE: Output enable in bidirectional mode.

/* @ref SPI_Frame_Format_define */
#define SPI_Frame_Format_MSB_transmitted_first    (0x00000000UL)
#define SPI_Frame_Format_LSB_transmitted_first    (0x1U << 7)               // Bit 7.1 >>LSB_transmitted_first

/* @ref SPI_Data_Size_define */
#define SPI_Data_Size_8bits                       (0x00000000UL)
#define SPI_Data_Size_16bits                      (0x1U << 11)              // Bit 11.1 >>16-bit data frame format is selected for transmission/reception

/* @ref SPI_CLK_Polarity_define */
#define SPI_CLK_Polarity_Idle_Low                 (0x00000000UL)
#define SPI_CLK_Polarity_Idle_High                (0x1U << 1)               // Bit1 >> CK to 1 when idle

/* @ref SPI_CLK_Phase_define */
#define SPI_CLK_Phase_first_clock_transition      (0x00000000UL)
#define SPI_CLK_Phase_second_clock_transition     (0x1U << 0)               // Bit 0 >> The second clock transition is the first data capture edge

/* @ref SPI_NSS_define */
#define SPI_NSS_HW_Slave                          (0x00000000UL)
#define SPI_NSS_HW_Master_ss_output_Enable        (0x1U << 2)
#define SPI_NSS_HW_Master_ss_output_Disable       ~(0x1U << 2)

#define SPI_NSS_SW_Set_SSI                        (0x1U<<9) | (0x1U<<8)
#define SPI_NSS_SW_Reset_SSI                      (0x1U<<9)

/* @ref SPI_CLK_Frequency_define */
#define SPI_CLK_Frequency_2                     (0x00000000UL)
#define SPI_CLK_Frequency_4                     (0b001U << 3)
#define SPI_CLK_Frequency_8                     (0b010U << 3)
#define SPI_CLK_Frequency_16                    (0b011U << 3)
#define SPI_CLK_Frequency_32                    (0b100U << 3)
#define SPI_CLK_Frequency_64                    (0b101U << 3)
#define SPI_CLK_Frequency_128                   (0b110U << 3)
#define SPI_CLK_Frequency_256                   (0b111U << 3)

/* @ref SPI_IRQ_Enable_define */
#define SPI_IRQ_Enable_NONE                        (uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE                       (uint32_t)(1 << 7)     // Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE                      (uint32_t)(1 << 6)     // RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE                       (uint32_t)(1 << 5)     // Error interrupt enable

enum Polling_Mech{
	Enable,
	Disable
};

/*******************************************************/

/*******************************************************/
/******* APIs Supported by "MCAL SPI DRIVER" ***********/
/*******************************************************/

void MCAL_SPI_Init(SPI_Typedef *SPIx, SPI_Config_t* SPI_config);
void MCAL_SPI_Deinit(SPI_Typedef *SPIx);

void MCAL_SPI_GPIO_SET_PINs(SPI_Typedef *SPIx);

void MCAL_SPI_SendData(SPI_Typedef *SPIx, uint16_t *TX_Buffer, enum Polling_Mech pollingEN);
void MCAL_SPI_ReceiveData(SPI_Typedef *SPIx, uint16_t *RX_Buffer, enum Polling_Mech pollingEN);

void MCAL_SPI_TX_RX(SPI_Typedef *SPIx, uint16_t *TX_Buffer, enum Polling_Mech pollingEN);

/*******************************************************/

#endif /* INC_STM32F103X8_SPI_DRIVER_H_ */
