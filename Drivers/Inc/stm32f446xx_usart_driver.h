
/**
 ******************************************************************************
 * @file    stm32f446xx_usart_driver.h
 * @author  Sunil Sutar
 * @brief   USART Driver Header File
 * @version 1.0
 * @date    July 2026
 *
 * @details
 * This file contains the declarations, data structures, macros,
 * and function prototypes required to configure and control the
 * Universal Synchronous Asynchronous Receiver Transmitter (USART) 
 * peripheral of the STM32F446RE microcontroller.
 *
 * Features:
 *  - USART Pin Configuration
 *  - USART Peripheral Clock Control
 *  - USART Initialization
 *  - USART Send Char
 *  - USART Send String
 *  - USART Reveive Char
 *  - USART Interrupt Configuration
 *  - USART Interrupt Handling
 *
 ******************************************************************************
 */

#ifndef STM32F446XX_USART_DRIVER_H_
#define STM32F446XX_USART_DRIVER_H_

#include "stm32f446xx.h"
#include <string.h>

#include "ring_buffer.h"

/********************************************************************
 * Configuration Structure for USARTx Peripheral
 ********************************************************************/

typedef struct
{
    uint8_t UART_Mode;                  /*!< possible values from @USART_Mode           >*/
    uint32_t UART_BaudRate;             /*!< possible values from @USART_BaudRate       >*/
    uint8_t UART_NoOfStopBits;          /*!< possible values from @USART_NoOfStopBits   >*/
    uint8_t UART_WordLength;            /*!< possible values from @USART_WordLength     >*/
    uint8_t UART_ParityControl;         /*!< possible values from @USART_ParityControl  >*/
    uint8_t UART_HWFlowControl;         /*!< possible values from @USART_HwFlowControl  >*/
}USART_Config_t;

/********************************************************************
 * Handle Structure for USARTx Peripheral
 ********************************************************************/

typedef struct
{
	USART_RegDef_t *pUSARTx;
	USART_Config_t USART_Config;
    
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;

    uint32_t TxLen;
    uint32_t RxLen;

    uint8_t TxBusyState;
    uint8_t RxBusyState;

    /* Ring Buffers */
    RingBuffer_t TxRingBuffer;
    RingBuffer_t RxRingBuffer;

}USART_Handle_t;

/********************************************************************
 * @USART_Mode
********************************************************************/
#define USART_MODE_ONLY_TX		0
#define USART_MODE_ONLY_RX		1
#define USART_MODE_TXRX	        2

/********************************************************************
 * @USART_BaudRate
********************************************************************/
#define USART_STD_BAUD_1200			1200
#define USART_STD_BAUD_2400			2400
#define USART_STD_BAUD_9600			9600
#define USART_STD_BAUD_19200		19200
#define USART_STD_BAUD_38400		38400
#define USART_STD_BAUD_57600		57600
#define USART_STD_BAUD_115200		115200
#define USART_STD_BAUD_230400		230400
#define USART_STD_BAUD_921600		921600
#define USART_STD_BAUD_2M			2000000
#define USART_STD_BAUD_3M			3000000

/********************************************************************
 * @USART_NoOfStopBits
********************************************************************/
#define USART_STOPBITS_1			0
#define USART_STOPBITS_0_5			1
#define USART_STOPBITS_1_5			2
#define USART_STOPBITS_2			3

/********************************************************************
 * @USART_WordLength
********************************************************************/
#define USART_WORDLEN_8BITS			0
#define USART_WORDLEN_9BITS			1

/********************************************************************
 * @USART_ParityControl
 ********************************************************************/
#define USART_PARITY_DISABLE		0
#define USART_PARITY_EVEN		    1
#define USART_PARITY_ODD  		    2

/********************************************************************
 * @USART_HwFlowControl
 *******************************************************************/
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

/********************************************************************
 * USART Flags
 *******************************************************************/
#define USART_FLAG_TXE				(1 << USART_SR_TXE)
#define USART_FLAG_RXNE				(1 << USART_SR_RXNE)
#define USART_FLAG_TC				(1 << USART_SR_TC)

/********************************************************************
 * USART Busy State Macros
 *******************************************************************/
#define USART_READY             0
#define USART_BUSY_IN_RX        1
#define USART_BUSY_IN_TX        2

/********************************************************************
 * USART Event Macros
 *******************************************************************/
#define USART_EVENT_TX_CMPLT    1
#define USART_EVENT_RX_CMPLT    2
#define USART_EVENT_IDLE        3
#define USART_EVENT_CTS         4
#define USART_ERR_FE            5
#define USART_ERR_NE            6
#define USART_ERR_ORE           7

/**********************************************************************
 * USART DRIVER APIS
 *********************************************************************/

/* Peripheral Clock */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t Enable);

/* USART Init and DeInit */
void USART_Init(USART_Handle_t *pUARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);

/* USART Data Send and Receive */
void USART_SendData(USART_Handle_t *pUARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len);



uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len);

void USART_SendString(USART_Handle_t *pUSARTHandle, const char *pStr);

/* Other Peripheral Control APIs */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Enable);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t FlagName);

/* Interrupt Configuration */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Enable);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

void USART_SendChar(USART_Handle_t *pUARTHandle, char ch);
char USART_ReceiveChar(USART_Handle_t *pUARTHandle);
void USART_ReceiveString(USART_Handle_t *pUARTHandle, char *buffer, uint32_t maxLen);

__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t AppEv);


#endif