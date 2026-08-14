
/**
 ******************************************************************************
 * @file    stm32f446xx_usart_driver.c
 * @author  Sunil Sutar
 * @brief   USART Driver Source File
 * @version 1.0
 * @date    July 2026
 *
 * @details
 * This file contains the implementation of USART peripheral driver
 * for STM32F446RE Microcontroller.
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


#include "stm32f446xx_usart_driver.h"

static void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);
static void USART_HandleTXEInterrupt(USART_Handle_t *pUSARTHandle);
static void USART_HandleTCInterrupt(USART_Handle_t *pUSARTHandle);
static void USART_HandleRXNEInterrupt(USART_Handle_t *pUSARTHandle);

__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t AppEv);


/*********************************************************************
 * @fn                - USART_PeriClockControl
 *
 * @brief             - Enables or disables the peripheral clock for
 *                      the specified USARTx Peripheral.
 *
 * @param[in]         - pUSARTx: Base address of the USARTx peripheral.
 * @param[in]         - EnorDi: ENABLE or DISABLE.
 *
 * @return            - None
 *
 *********************************************************************/

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pUSARTx == USART1)
        {
            USART1_PCLK_EN();        
        }
        else if(pUSARTx == USART2)
        {
            USART2_PCLK_EN();
        }
        else if(pUSARTx == USART3)
        {
            USART3_PCLK_EN();
        }
        else if(pUSARTx == UART4)
        {
            UART4_PCLK_EN();
        }
        else if(pUSARTx == UART5)
        {
            UART5_PCLK_EN();
        }
        else if(pUSARTx == USART6)
        {
            USART6_PCLK_EN();
        }
    }
    else
    {
        if(pUSARTx == USART1)
        {
            USART1_PCLK_DI();        
        }
        else if(pUSARTx == USART2)
        {
            USART2_PCLK_DI();
        }
        else if(pUSARTx == USART3)
        {
            USART3_PCLK_DI();
        }
        else if(pUSARTx == UART4)
        {
            UART4_PCLK_DI();
        }
        else if(pUSARTx == UART5)
        {
            UART5_PCLK_DI();
        }
        else if(pUSARTx == USART6)
        {
            USART6_PCLK_DI();
        }
    }
}

/*********************************************************************
 * @fn                - USART_Init
 *
 * @brief             - Initializes the USART peripheral.
 *
 * @details
 * This function configures the specified USART peripheral according to the
 * settings provided in the USART handle structure. 
 * The following parameters are configured:
 * - Baud rate
 * - Word length
 * - Number of stop bits
 * - Parity control
 * - Hardware flow control
 * - USART operating mode (Transmit/Receive)
 * 
 * @param[in]         - pUARTHandle: Pointer to the USART handle.
 *
 * @return            - None
 *
 * @note
 * - The corresponding GPIO pins must be configured in Alternate Function
 *   mode before enabling the USART peripheral.
 * - The USART peripheral remains disabled after initialization. Call
 *   USART_PeripheralControl() to enable communication.
 * - Ensure the peripheral clock source is correctly configured
 *
 * @warning
 * Reinitializing an active USART peripheral may interrupt ongoing
 * transmission or reception. Disable the peripheral before changing
 * its configuration.
 * 
 *********************************************************************/

void USART_Init(USART_Handle_t *pUARTHandle)
{
    uint32_t tempreg = 0;

    /* 1. Enable Peripheral Clock */
    USART_PeriClockControl(USART2, ENABLE);

    /**************** Configuration of CR1 ***********************/
    /* 2. Configure UART Mode */
    switch(pUARTHandle->USART_Config.UART_Mode)
    {
        case USART_MODE_ONLY_TX:
            tempreg |= (1 << USART_CR1_TE);
            break;
        
        case USART_MODE_ONLY_RX:
            tempreg |= (1 << USART_CR1_RE);
            break;

        case USART_MODE_TXRX:
            tempreg |= (1 << USART_CR1_TE);
            tempreg |= (1 << USART_CR1_RE);
            break;
    }

    /* 3. Configuration of Word Length */
    tempreg |= (pUARTHandle->USART_Config.UART_WordLength << USART_CR1_M);


    /* 4. Configuration of parity control  */
    if(pUARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
    {
        //Disable Parity
        tempreg &= ~(1 << USART_CR1_PCE);
    }
    else if(pUARTHandle->USART_Config.UART_ParityControl == USART_PARITY_EVEN)
    {
        //Enable Parity
        tempreg |= (1 << USART_CR1_PCE);

        //Even Parity Selection
        tempreg &= ~(1 << USART_CR1_PS);
    }
    else if(pUARTHandle->USART_Config.UART_ParityControl == USART_PARITY_ODD)
    {
        //Enable Parity
        tempreg |= (1 << USART_CR1_PCE);

        //Odd Parity Selection
        tempreg |= (1 << USART_CR1_PS);  
    }


    /* program CR1 register */
    pUARTHandle->pUSARTx->CR1 = tempreg;

    /**************** Configuration of CR2 ***********************/
    tempreg = 0;

    /* Configure number of stop bits */
    tempreg |= pUARTHandle->USART_Config.UART_NoOfStopBits << USART_CR2_STOP;

    /* program CR2 register */
    pUARTHandle->pUSARTx->CR2 = tempreg;

    /*************** Configuration of CR3 ************************/
    tempreg = 0;

    /* Configure HwFlow Control */
    if(pUARTHandle->USART_Config.UART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        tempreg |= (1 << USART_CR3_CTSE);
    }
    else if(pUARTHandle->USART_Config.UART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        tempreg |= (1 << USART_CR3_RTSE);
    }
    else if(pUARTHandle->USART_Config.UART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        tempreg |= ((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE));
    }    

    /* program CR3 register */
    pUARTHandle->pUSARTx->CR3 = tempreg;

    /*  Configuration of BRR(Baudrate register) */
    USART_SetBaudRate(pUARTHandle->pUSARTx, pUARTHandle->USART_Config.UART_BaudRate);

    /* Enable USART */
    USART_PeripheralControl(pUARTHandle->pUSARTx, ENABLE);

}

/*********************************************************************
 * @fn                - USART_DeInit
 *
 * @brief             - Deinitialize the specified USART peripheral.
 *
 * @param[in]         - pUSARTx: Base address of the USART peripheral.
 *
 * @return            - None
 *
 *********************************************************************/

void USART_DeInit(USART_RegDef_t *pUSARTx)
{
    if(pUSARTx == USART1)
    {
        USART1_REG_RESET();
    }
    else if(pUSARTx == USART2)
    {
        USART2_REG_RESET();
    }
    else if(pUSARTx == USART2)
    {
        USART2_REG_RESET();
    }
    else if(pUSARTx == USART3)
    {
        USART3_REG_RESET();
    }
    else if(pUSARTx == UART4)
    {
        UART4_REG_RESET();
    }
    else if(pUSARTx == UART5)
    {
        UART5_REG_RESET();
    }
    else if(pUSARTx == USART6)
    {
        USART6_REG_RESET();
    }
}

/*********************************************************************
 * @fn                - USART_SendData
 *
 * @brief             - Sends data over the USART peripheral in polling mode.
 *
 * @param[in]         - pUARTHandle : Pointer to the USART handle.
 * @param[in]         - pTxBuffer   : Pointer to the transmit data buffer.
 * @param[in]         - Len         : Number of bytes to transmit.
 * 
 * @return            - None
 *
 * @note              - This is a blocking (polling) API.
 *                    - The function returns only after all data has been transmitted.
 *
 * @warning           - This function blocks the CPU until transmission is complete and is not
 *                      suitable for time-critical applications. For non-blocking communication,
 *                      use the interrupt or DMA-based transmit API.
 * 
 *********************************************************************/

void USART_SendData(USART_Handle_t *pUARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint16_t *pData;

    for(uint32_t i = 0; i < Len; i++)
    {
        /* wait until TXE flag is set */
        while(! USART_GetFlagStatus(pUARTHandle->pUSARTx, USART_FLAG_TXE));

        /* Check the USART_WordLength item for 9BIT or 8BIT in a frame */
        if(pUARTHandle->USART_Config.UART_WordLength == USART_WORDLEN_9BITS)
        {
            //9-bit Word Length
            pData = (uint16_t *) pTxBuffer;
            pUARTHandle->pUSARTx->DR = *pData & (uint16_t)0x01FFU;

            /* check for USART_ParityControl */
            if(pUARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
            {
                //No Parity : 9-bits Data
                //Increment pTxBuffer twice
                pTxBuffer++;
                pTxBuffer++;
            }
            else
            {
                //1-bit: Parity and 8-bit: Data
                //Increment pTxBuffer
                pTxBuffer++;
            }
        }
        else
        {
            //8-bit Word Length
            pUARTHandle->pUSARTx->DR = (uint16_t)(*pTxBuffer & 0xFFU);

            //Increment pTxBuffer
            pTxBuffer++;

        }
    }

    /* wait till TC flag is set */
    while(! USART_GetFlagStatus(pUARTHandle->pUSARTx, USART_FLAG_TC));
}

/*********************************************************************
 * @fn                - USART_ReceiveData
 *
 * @brief             - Receives data from the USART peripheral in polling mode.
 *
 * @param[in]         - pUARTHandle : Pointer to the USART handle.
 * @param[in]         - pRxBuffer   : Pointer to the receive data buffer.
 * @param[in]         - Len         : Number of bytes to receive.
 * 
 * @return            - None
 *
 * @note              - This is a blocking (polling) API.
 *                    - The function returns only after all data has been received.
 *
 * @warning           - This function blocks the CPU until transmission is complete and is not
 *                      suitable for time-critical applications. For non-blocking communication,
 *                      use the interrupt or DMA-based transmit API.
 * 
 *********************************************************************/

void USART_ReceiveData(USART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        /* Wait until RXNE flag is set */
        while(!  USART_GetFlagStatus(pUARTHandle->pUSARTx, USART_FLAG_RXNE));

        /* Check the USART_WordLength : 8-bit or 9-bit */
        if(pUARTHandle->USART_Config.UART_WordLength == USART_WORDLEN_9BITS)
        {
            //9-bits
            //Check Parity
            if(pUARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
            {
                //No Parity -> 9-bit Data
                *((uint16_t *)pRxBuffer) = pUARTHandle->pUSARTx->DR & 0x1FFU;

                //Increment pRxBuffer
                pRxBuffer++;
                pRxBuffer++;
            }
            else
            {   
                //Parity -> 1-bit Parity + 8-bit Data
                *pRxBuffer = pUARTHandle->pUSARTx->DR & 0xFF;

                //Increment pRxBuffer
                pRxBuffer++;
            }
        }
        else
        {
            //8-bits
            //Check Parity
            if(pUARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
            {
                //No Parity -> 8-bit Data
                *pRxBuffer = pUARTHandle->pUSARTx->DR & 0xFF;
            }
            else
            {
                //Parity -> 1-bit Parity + 7-bit Data
                *pRxBuffer = (uint8_t) pUARTHandle->pUSARTx->DR & 0x7F;
            }

            //Increment pRxBuffer
            pRxBuffer++;
        }
    }
}

/*********************************************************************
 * @fn                - USART_SendString
 *
 * @brief             - Sends a null-terminated string over the USART peripheral.
 *
 * @param[in]         - pUARTHandle : Pointer to the USART handle structure
 * @param[in]         - pStr        : Pointer to the null-terminated string to be transmitted.
 * 
 * @return            - None
 * 
 * @note              - This is a blocking (polling) API.
 *                    - The function returns only after all data has been transmitted.
 *
 * @warning           - This function blocks the CPU until transmission is complete and is not
 *                      suitable for time-critical applications. For non-blocking communication,
 *                      use the interrupt or DMA-based transmit API.
 * 
 *********************************************************************/

void USART_SendString(USART_Handle_t *pUSARTHandle, const char *pStr)
{
   //USART_SendData(pUSARTHandle, (uint8_t *)pStr, strlen(pStr)); 

   while(*pStr != '\0')
   {
        /* Wait until transmit data register is empty */
        while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE));

        pUSARTHandle->pUSARTx->DR = (uint8_t)*pStr;

        pStr++;
   }

    /* Wait for Transmission Complete */
    while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC));

}

/*********************************************************************
 * @fn                - USART_PeripheralControl
 *
 * @brief             - Enables or disables the USART peripheral.
 *
 * @param[in]         - pUSARTx: Base address of the USARTx peripheral.
 * @param[in]         - Enable : ENABLE or DISABLE.
 *
 * @return            - None
 *
 * @note
 * - The USART peripheral should be configured before enabling it.
 * - Disabling the peripheral during an ongoing transmission or reception
 *   may result in data loss.
 *
 * @warning
 * Ensure that any ongoing communication has completed before disabling
 * the USART peripheral.
 * 
 *********************************************************************/

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Enable)
{
    if(Enable == ENABLE)
    {
        pUSARTx->CR1 |= (1 << USART_CR1_UE);
    }
    else
    {
        pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
    }
}

/*********************************************************************
 * @fn                - USART_GetFlagStatus
 *
 * @brief             - Returns the status of the specified USART status flag.
 *                    - The API can be used to monitor various USART events such as:
 *                          - Transmit Data Register Empty (TXE)
 *                          - Transmission Complete (TC)
 *                          - Receive Data Register Not Empty (RXNE)
 *                          - Overrun Error (ORE)
 *                          - Framing Error (FE)
 *                          - Noise Error (NE)
 *                          - Parity Error (PE)
 *                          - Idle Line Detected (IDLE)
 *  
 * @param[in]         - pUSARTx: Base address of the USARTx peripheral.
 * @param[in]         - Enable : ENABLE or DISABLE.
 *
 * @return            -  uint8_t
 * @retval FLAG_SET   - The specified flag is set.
 * @retval FLAG_RESET - The specified flag is reset.
 * 
 *  * @note
 * This function only reads the status of the specified flag and does not
 * clear it. Some USART flags require a specific software sequence to clear
 * them as described in the STM32 reference manual.
 *
 * @warning
 * Ensure that the supplied flag is valid for the selected USART peripheral.
 * 
 *********************************************************************/

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t FlagName)
{
    if(pUSARTx->SR & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

/*********************************************************************
 * @fn                - USART_SetBaudRate
 *
 * @brief             - Configures the USART Baudrate
 *
 * @param[in]         - pUSARTx: Pointer to the USART Peripheral Reg Def.
 * @param[in]         - BaudRate: BaudRate likes 115200 or 9600 and so on.
 * 
 * @return            - None
 *
 *********************************************************************/

static void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
    uint32_t Fpclk;
    uint32_t usartdiv;
    uint32_t mantissa, fraction;

    uint32_t tempreg = 0;

    if(pUSARTx == USART1 || pUSARTx == USART6)
    {
       Fpclk = RCC_GetPCLK2Value();
    }
    else
    {
       Fpclk = RCC_GetPCLK1Value();
    }

    /* Check for OVER8 configuration bit */
    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
    {
        //Oversampling by 8
        usartdiv = ((25U * Fpclk) / (2U * BaudRate));
    }
    else
    {
        //Oversampling by 16
        usartdiv = ((25U * Fpclk) / (4U * BaudRate));
    }

    /* Calculate the Mantissa part */
    mantissa = usartdiv / 100U;

    tempreg |= mantissa << 4;

    /* Extract the fraction part */
    fraction = (usartdiv - (mantissa * 100U));

    /* Calculation of the final fractional */
    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
    {
        //Oversampling by 8
        fraction = ((fraction * 8U) + 50U)/ 100U;
    }
    else
    {
        //Oversampling by 16
        fraction = ((fraction * 16U) + 50U)/ 100U;
    }

    tempreg |= fraction & 0x0F;

    /* copy the value of tempreg in to BRR register */
    pUSARTx->BRR = tempreg;
}

/*********************************************************************
 * @fn                - USART_SendDataIT
 *
 * @brief             - Transmits data over the USART peripheral using interrupt mode.
 *
 * @param[in]         - pUARTHandle : Pointer to the USART handle.
 * @param[in]         - pTxBuffer   : Pointer to the transmit data buffer.
 * @param[in]         - Len         : Number of bytes to transmit.
 * 
 * @return            - uint8_t
 *                      @retval USART_READY      : Transmission started successfully.
 *                      @retval USART_BUSY_IN_TX : USART is currently busy transmitting data.
 * 
 * @note
 * - This is a non-blocking API.
 * - The function returns immediately after enabling the USART interrupts.
 * - The transmit buffer must remain valid until the transmission completes.
 * - The application must implement the USART interrupt handler and enable
 *   the corresponding NVIC interrupt.
 *
 * @warning
 * Do not modify or free the transmit buffer until the transmission is
 * complete. Doing so may result in corrupted transmitted data.
 * 
 *********************************************************************/

uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t txState = pUSARTHandle->TxBusyState;

    /* Start a new transmission only if USART is ready */
    if(txState != USART_BUSY_IN_TX)
    {
        pUSARTHandle->pTxBuffer = pTxBuffer;
        pUSARTHandle->TxLen = Len;
        pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

        /* Enable TXE interrupt */
        pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);
    }

    return txState;
}

/*********************************************************************
 * @fn                - USART_ReceiveDataIT
 *
 * @brief             - Receives data from the USART peripheral using interrupt mode.
 *
 * @param[in]         - pUARTHandle : Pointer to the USART handle.
 * @param[in]         - pRxBuffer   : Pointer to the receive data buffer.
 * @param[in]         - Len         : Number of bytes to receive.
 * 
 * @return            - uint8_t
 *                      @retval USART_READY      : Reception  started successfully.
 *                      @retval USART_BUSY_IN_RX : USART is currently busy receiving data.
 * 
 * @note
 * - This is a non-blocking API.
 * - The function returns immediately after enabling the RXNE interrupt.
 * - The receive buffer must remain valid until the reception is complete.
 * - The application must implement the USART interrupt handler and enable
 *   the corresponding NVIC interrupt.
 *
 * @warning
 * Do not modify or free the receive buffer until the reception is complete.
 * Doing so may result in corrupted received data.
 * 
 *********************************************************************/

uint8_t USART_ReceiveDataIT(USART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t rxState = pUARTHandle->RxBusyState;

    if(rxState != USART_BUSY_IN_RX)
    {
        pUARTHandle->pRxBuffer = pRxBuffer;
        pUARTHandle->RxLen = Len;
        pUARTHandle->RxBusyState = USART_BUSY_IN_RX;

        /* Enable RXNE interrupt */
        pUARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);
    }

    return rxState;
}

/*********************************************************************
 * @fn                - USART_IRQInterruptConfig
 *
 * @brief             - Enables or disables the specified IRQ in the NVIC.
 *
 * @param[in]         - IRQNumber: IRQ number to be configured.
 * @param[in]         - Enable: ENABLE or DISABLE.
 *
 * @return            - None
 *
 *********************************************************************/

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Enable)
{
    if(Enable == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << IRQNumber % 32);
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << IRQNumber % 64);
        }
    }
    else
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << IRQNumber % 32);
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER1 |= (1 << IRQNumber % 64);
        }
    }
}

/*********************************************************************
 * @fn                - USART_IRQPriorityConfig
 *
 * @brief             - Configures the priority of a USART interrupt.
 *
 * @param[in]         - IRQNumber: IRQ number to be configured.
 * @param[in]         - IRQPriority: Priority to be assigned to the IRQ.
 *
 * @return            - None
 *
 *********************************************************************/

void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    //1. First Finding out Priority Register and section in priority register
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    //Lower 4-bits are not Implement in each IPR section
    uint8_t shift_ammount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    //Program NVIC_PR Register
    *(NVIC_PR_BASE_ADDR + iprx) &= ~(0xFU << shift_ammount);
    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_ammount);
}

/*********************************************************************
 * @fn                - USART_IRQHandling
 *
 * @brief             - Handles the USART interrupts.
 *
 * @param[in]         - pUSARTHandle: Pointer to the USART handle.
 *
 * @return            - None
 *
 *********************************************************************/

void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
    /**************************************************************
     * Check for TXE Flag
     **************************************************************/
    USART_HandleTXEInterrupt(pUSARTHandle);
    
    /**************************************************************
     * Check for TC Flag
    **************************************************************/
    USART_HandleTCInterrupt(pUSARTHandle);
    
    /**************************************************************
     * Check for RXNE Flag
    **************************************************************/
    USART_HandleRXNEInterrupt(pUSARTHandle);
}

/*********************************************************************
 * @fn                - USART_HandleTXEInterrupt
 *
 * @brief             - Handles the USART TXE interrupts.
 *
 * @param[in]         - pUSARTHandle: Pointer to the USART handle.
 *
 * @return            - None
 *
 *********************************************************************/

static void USART_HandleTXEInterrupt(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1 , temp2;
    uint16_t *pdata;

	//Implement the code to check the state of TXE bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TXE);

	//Implement the code to check the state of TXEIE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TXEIE);


	if(temp1 && temp2 )
	{
		//this interrupt is because of TXE

		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			//Keep sending data until Txlen reaches to zero
			if(pUSARTHandle->TxLen > 0)
			{
				//Check the USART_WordLength item for 9BIT or 8BIT in a frame
				if(pUSARTHandle->USART_Config.UART_WordLength == USART_WORDLEN_9BITS)
				{
					//if 9BIT load the DR with 2bytes masking  the bits other than first 9 bits
					pdata = (uint16_t*) pUSARTHandle->pTxBuffer;
					pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

					//check for USART_ParityControl
					if(pUSARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
					{
						//No parity is used in this transfer , so 9bits of user data will be sent
						//Implement the code to increment pTxBuffer twice
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->TxLen-=2;
					}
					else
					{
						//Parity bit is used in this transfer . so 8bits of user data will be sent
						//The 9th bit will be replaced by parity bit by the hardware
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->TxLen-=1;
					}
				}
				else
				{
					//This is 8bit data transfer
					pUSARTHandle->pUSARTx->DR = (*pUSARTHandle->pTxBuffer  & (uint8_t)0xFF);

					//Implement the code to increment the buffer address
					pUSARTHandle->pTxBuffer++;
					pUSARTHandle->TxLen-=1;
				}

			}
			if (pUSARTHandle->TxLen == 0 )
			{
				//TxLen is zero
				//Implement the code to clear the TXEIE bit (disable interrupt for TXE flag )
				pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_TXEIE);

                /* Enable TC interrupt */
				pUSARTHandle->pUSARTx->CR1 |= ( 1 << USART_CR1_TCIE);
			}
		}
	}
}

/*********************************************************************
 * @fn                - USART_HandleTXEInterrupt
 *
 * @brief             - Handles the USART TC interrupts.
 *
 * @param[in]         - pUSARTHandle: Pointer to the USART handle.
 *
 * @return            - None
 *
 *********************************************************************/

static void USART_HandleTCInterrupt(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1 , temp2;

    /* Check if transmission is actually complete */
    temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TC);
    temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TCIE);

    if(temp1 && temp2)
    {
        if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
        {
            if(!pUSARTHandle->TxLen)
            {
                /* Disable TC interrupt */
                pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TCIE);

                /* Clear transmission busy state */
                pUSARTHandle->TxBusyState = USART_READY;

                /* Reset transmit buffer information */
                pUSARTHandle->pTxBuffer = NULL;
                pUSARTHandle->TxLen = 0;

                /* Notify the application */
                USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_TX_CMPLT);
            }
        }
    }
}

/*********************************************************************
 * @fn                - USART_HandleTXEInterrupt
 *
 * @brief             - Handles the USART RXNE interrupts.
 *
 * @param[in]         - pUSARTHandle: Pointer to the USART handle.
 *
 * @return            - None
 *
 *********************************************************************/

static void USART_HandleRXNEInterrupt(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1 , temp2;

	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_RXNE);
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_RXNEIE);

	if(temp1 && temp2 )
	{
		//this interrupt is because of rxne
		if(pUSARTHandle->RxBusyState == USART_BUSY_IN_RX)
		{
			if(pUSARTHandle->RxLen > 0)
			{
				//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
				if(pUSARTHandle->USART_Config.UART_WordLength == USART_WORDLEN_9BITS)
				{
					//We are going to receive 9bit data in a frame

					//Now, check are we using USART_ParityControl control or not
					if(pUSARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
					{
						//No parity is used , so all 9bits will be of user data
						//read only first 9 bits so mask the DR with 0x01FF
						*((uint16_t*) pUSARTHandle->pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);

						//Now increment the pRxBuffer two times
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->RxLen-=2;
					}
					else
					{
						//Parity is used, so 8bits will be of user data and 1 bit is parity
						*pUSARTHandle->pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->RxLen-=1;
					}
				}
				else
				{
					//We are going to receive 8bit data in a frame
					//Now, check are we using USART_ParityControl control or not
					if(pUSARTHandle->USART_Config.UART_ParityControl == USART_PARITY_DISABLE)
					{
						//No parity is used , so all 8bits will be of user data

						//read 8 bits from DR
						 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
					}
					else
					{
						//Parity is used, so , 7 bits will be of user data and 1 bit is parity

						//read only 7 bits , hence mask the DR with 0X7F
						 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);
					}

					//Now , increment the pRxBuffer
					pUSARTHandle->pRxBuffer++;
					pUSARTHandle->RxLen-=1;
				}
			}

			if(! pUSARTHandle->RxLen)
			{
				//disable the rxne
				pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_RXNEIE );
				pUSARTHandle->RxBusyState = USART_READY;
				USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_RX_CMPLT);
			}
		}
	}
}

__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t AppEv)
{
    /* User application may override this function */
    /* Default implementation */
    (void)pUSARTHandle;
    (void)AppEv;
}

void USART_SendChar(USART_Handle_t *pUARTHandle, char ch)
{
    /* Wait until TXE Flag is Set */
    while(!(pUARTHandle->pUSARTx->SR & (1U << USART_SR_TXE)));

    pUARTHandle->pUSARTx->DR = ch;
}

char USART_ReceiveChar(USART_Handle_t *pUARTHandle)
{
    /* check RXNE Flag  */
    while(!(pUARTHandle->pUSARTx->SR & (1U << USART_SR_RXNE)));

    return (char)pUARTHandle->pUSARTx->DR;
}

void USART_ReceiveString(USART_Handle_t *pUARTHandle, char *buffer, uint32_t maxLen)
{
    uint32_t i = 0;

    while(i < (maxLen - 1))
    {
        char ch = USART_ReceiveChar(pUARTHandle);

        /* Echo back */
        USART_SendChar(pUARTHandle, ch);

        if(ch == '\r' || ch == '\n')
        {
            break;
        }

        buffer[i++] = ch;
    }

    buffer[i] = '\0';
}