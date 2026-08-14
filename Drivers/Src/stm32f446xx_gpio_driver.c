
/**
 ******************************************************************************
 * @file    stm32f446xx_gpio_driver.c
 * @author  Sunil Sutar
 * @brief   GPIO Driver Source File
 * @version 1.0
 * @date    July 2026
 *
 * @details
 * This file contains the implementation of GPIO peripheral driver
 * for STM32F446RE Microcontroller.
 *
 * Features:
 *  - GPIO Initialization
 *  - GPIO Deinitialization
 *  - Read/Write GPIO Pin
 *  - Read/Write GPIO Port 
 *  - Toggle GPIO Pin
 *  - GPIO Interrupt Configuration (EXTI)
 *  - GPIO Interrupt Handling (EXTI)
 * 
 ******************************************************************************
 */

#include "stm32f446xx_gpio_driver.h"

static uint8_t GPIO_GetPortCode(GPIO_RegDef_t *pGPIOx);

/*********************************************************************
 * @fn                - GPIO_PeriClockControl
 *
 * @brief             - Enables or disables the peripheral clock for
 *                      the specified GPIO port.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 * @param[in]         - EnorDi: ENABLE or DISABLE.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t Enable)
{
    if(Enable == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
    }
}

/*********************************************************************
 * @fn                - GPIO_Init
 *
 * @brief             - Initializes the GPIO peripheral.
 *
 * @param[in]         - pGPIOHandle: Pointer to the GPIO handle.
 *
 * @return            - None
 *
 * @note              - Configures the selected GPIO pin based on the
 *                      parameters in the GPIO handle structure.
 *
 *********************************************************************/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t tempreg = 0;

    /* Enable GPIO Peripheral Clock */
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    /* 1. Configure GPIO Mode */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        //Non-Interrupt Mode
        tempreg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3U << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER |= tempreg;
    }
    else
    {
        //Interrupt Mode
        //1. Configure Trigger Selection
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            //Falling Edge
            EXTI->FTSR |= (1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR &= ~(1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            //Rising Edge
            EXTI->RTSR |= (1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR &= ~(1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);   
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            //Rising Edge + Falling Edge
            EXTI->RTSR |= (1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR |= (1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);   
        }

        //2. Enable Clock for SYSCFG
        SYSCFG_PCLK_EN();

        //3. Configure the GPIO port selection in SYSCFG_EXTICR Register
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        uint8_t portcode = GPIO_GetPortCode(pGPIOHandle->pGPIOx);
        SYSCFG->EXTICR[temp1] |= portcode << (temp2 * 4);

        //4. Enable the EXTI Interrupt delivery using IMR
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    /* 2. Configure the GPIO Output Speed */
    tempreg = 0;
    tempreg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3U << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= tempreg;

    /* 3. Configure the GPIO PuPd Settings */
    tempreg = 0;
    tempreg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3U << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= tempreg;

    /* 4. Configure the GPIO Output Type */
    tempreg = 0;
    tempreg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= tempreg;

    /* 5. Configure the GPIO Alt Functionality */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t regIndex;
        uint8_t bitPosition;

        regIndex = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8U;
        bitPosition = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8U) * 4);

        pGPIOHandle->pGPIOx->AFR[regIndex] &= ~(0xFU << bitPosition);   //clearing
        pGPIOHandle->pGPIOx->AFR[regIndex] |= ((pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode & 0xFU) << bitPosition);
    }
}

/*********************************************************************
 * @fn                - GPIO_DeInit
 *
 * @brief             - Resets the specified GPIO peripheral.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if(pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
}

/*********************************************************************
 * @fn                - GPIO_ReadFromInputPin
 *
 * @brief             - Reads the logic level of the specified GPIO pin.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 * @param[in]         - PinNumber: GPIO pin number.
 *
 * @return            - GPIO pin status (SET or RESET).
 *
 *********************************************************************/

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;

    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x01);

    return value;
}

/*********************************************************************
 * @fn                - GPIO_ReadFromInputPort
 *
 * @brief             - Reads the input value of the specified GPIO port.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 *
 * @return            - 16-bit value representing the input state of
 *                      all GPIO pins.
 *
 *********************************************************************/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint16_t)(pGPIOx->IDR);
}

/*********************************************************************
 * @fn                - GPIO_WriteToOutputPin
 *
 * @brief             - Writes a value to the specified GPIO output pin.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 * @param[in]         - PinNumber: GPIO pin number.
 * @param[in]         - Value: GPIO_PIN_SET or GPIO_PIN_RESET.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->BSRR = (1U << PinNumber);
    }
    else
    {
        pGPIOx->BSRR = (1U << (PinNumber + 16U));
    }
}

/*********************************************************************
 * @fn                - GPIO_WriteToOutputPort
 *
 * @brief             - Writes a value to the GPIO output port.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 * @param[in]         - Value: Value to be written to the output port.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}

/*********************************************************************
 * @fn                - GPIO_ToggleOutputPin
 *
 * @brief             - Toggles the state of the specified GPIO output pin.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 * @param[in]         - PinNumber: GPIO pin number to be toggled.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1U << PinNumber);
}

/*********************************************************************
 * @fn                - GPIO_IRQInterruptConfig
 *
 * @brief             - Enables or disables the specified IRQ in the NVIC.
 *
 * @param[in]         - IRQNumber: IRQ number to be configured.
 * @param[in]         - Enable: ENABLE or DISABLE.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Enable)
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
 * @fn                - GPIO_IRQPriorityConfig
 *
 * @brief             - Configures the priority of a GPIO interrupt.
 *
 * @param[in]         - IRQNumber: IRQ number to be configured.
 * @param[in]         - IRQPriority: Priority to be assigned to the IRQ.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
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
 * @fn                - GPIO_IRQHandling
 *
 * @brief             - Handles the GPIO interrupt for the specified pin.
 *
 * @param[in]         - PinNumber: GPIO pin number.
 *
 * @return            - None
 *
 *********************************************************************/

void GPIO_IRQHandling(uint8_t PinNumber)
{
    /* Check whether the interrupt is pending */
    if(EXTI->PR & (1 << PinNumber))
    {
        /* Clear the pending interrupt by writing 1 */
        EXTI->PR |= (1 << PinNumber);
    }
}

/*********************************************************************
 * @fn                - GPIO_GetPortCode
 *
 * @brief             - Returns the port code for the specified GPIO port.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral.
 *
 * @return            - GPIO port code.
 *
 *********************************************************************/

static uint8_t GPIO_GetPortCode(GPIO_RegDef_t *pGPIOx)
{
    if (pGPIOx == GPIOA) return GPIOA_PORT_CODE;
    else if (pGPIOx == GPIOB) return GPIOB_PORT_CODE;
    else if (pGPIOx == GPIOC) return GPIOC_PORT_CODE;
    else if (pGPIOx == GPIOD) return GPIOD_PORT_CODE;
    else if (pGPIOx == GPIOE) return GPIOE_PORT_CODE;
    else if (pGPIOx == GPIOF) return GPIOF_PORT_CODE;
    else if (pGPIOx == GPIOG) return GPIOG_PORT_CODE;
    else if (pGPIOx == GPIOH) return GPIOH_PORT_CODE;
    else 
        return 0;
}