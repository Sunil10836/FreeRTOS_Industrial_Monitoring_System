/*********************************************************************
 * @file              - stm32f446xx.h
 *
 * @author            - Sunil Sutar
 *
 * @brief             - Device header file for STM32F446RE
 *                      microcontroller.
 *
 * @details           - This file contains:
 *                      - Memory map definitions
 *                      - Peripheral register definitions
 *                      - Peripheral base addresses
 *                      - Clock enable/reset macros
 *                      - NVIC definitions
 *                      - Generic utility macros
 *
 * @version           - 1.0
 *
 * @date              - 10 July 2026
 *
 *********************************************************************/

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>

#define __vo    volatile

/************************ START: Processor Specific Details *********************/

/********************************************************************
 * ARM Cortex Mx Processor NVIC ISERx register addresses
 *******************************************************************/

#define NVIC_ISER0			 ((__vo uint32_t *) 0xE000E100 )
#define NVIC_ISER1			 ((__vo uint32_t *) 0xE000E104 )
#define NVIC_ISER2			 ((__vo uint32_t *) 0xE000E108 )
#define NVIC_ISER3			 ((__vo uint32_t *) 0xE000E10C )

/********************************************************************
 * ARM Cortex Mx Processor NVIC ISERx register addresses
 *******************************************************************/

#define NVIC_ICER0			 ((__vo uint32_t *) 0XE000E180 )
#define NVIC_ICER1			 ((__vo uint32_t *) 0XE000E184 )
#define NVIC_ICER2			 ((__vo uint32_t *) 0XE000E188 )
#define NVIC_ICER3			 ((__vo uint32_t *) 0XE000E18C )

#define NVIC_PR_BASE_ADDR      ((__vo uint32_t*)0xE000E400U)

#define NO_PR_BITS_IMPLEMENTED    4U

/************************ END: Processor Specific Details *********************/


/************************ START: MCU Specific Details ************************/

/********************************************************************
 * Base addresses of Flash and SRAM memories
 *******************************************************************/

#define FLASH_BASEADDR				0x08000000U				/* This is Base Address of FLASH memory  */
#define SRAM1_BASEADDR				0x20000000U				/* This is Base Address of SRAM1 memory  */
#define SRAM2_BASEADDR				0x2001C000U				/* This is Base Address of SRAM2 memory  */
#define ROM_BASEADDR				0x1FFF0000U				/* This is Base Address of ROM memory  */
#define SRAM 						SRAM1_BASEADDR

/********************************************************************
 * AHBx and APBx Bus Peripheral base addresses
 *******************************************************************/

#define PERIPH_BASEADDR		   		0x40000000U
#define APB1PERIPH_BASEADDR	   		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR			0x40010000U
#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x50000000U


/********************************************************************
 * Base addresses of peripherals which are hanging on AHB1 bus
 *******************************************************************/

#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)

#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)

/********************************************************************
 * Base addresses of peripherals which are hanging on APB1 bus
 *******************************************************************/

#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)

/********************************************************************
 * Base addresses of peripherals which are hanging on APB2 bus
 *******************************************************************/

#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR				(APB2PERIPH_BASEADDR + 0x3400)

#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)

#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)

#define ADC1_BASEADDR                    (APB2PERIPH_BASEADDR + 0x2000)
#define ADC2_BASEADDR                    (APB2PERIPH_BASEADDR + 0x2100)
#define ADC3_BASEADDR                    (APB2PERIPH_BASEADDR + 0x2200)
#define ADC_COMMON_BASEADDR              (APB2PERIPH_BASEADDR + 0x2300)

/********************************************************************
 * GPIO register definition structure
 *******************************************************************/

typedef struct
{
	__vo uint32_t MODER;             	/* GPIO port mode register, 		          Address offset: 0x00 */
	__vo uint32_t OTYPER;              /* GPIO port output type register,  		Address offset: 0x04 */
	__vo uint32_t OSPEEDR;			/* GPIO port output speed register, 		Address offset: 0x08 */
	__vo uint32_t PUPDR;			/* GPIO port pull-up/pull-down register,     Address offset: 0x0C */
	__vo uint32_t IDR;				/* GPIO port input data register, 		     Address offset: 0x10 */
	__vo uint32_t ODR;				/* GPIO port output data register, 		Address offset: 0x14 */
	__vo uint32_t BSRR;				/* GPIO port bit set/reset register, 		Address offset: 0x18 */
	__vo uint32_t LCKR;				/* GPIO port configuration lock register,    Address offset: 0x1C */
	__vo uint32_t AFR[2];			/* AFR[0] : GPIO alternate function low register, AF[1] : GPIO alternate function high register Address offset: 0x20-0x24 */

}GPIO_RegDef_t;

/********************************************************************
 * RCC register definition structure
 *******************************************************************/

typedef struct
{
  __vo uint32_t CR;            /* TODO,     										Address offset: 0x00 */
  __vo uint32_t PLLCFGR;       /* TODO,     										Address offset: 0x04 */
  __vo uint32_t CFGR;          /* TODO,     										Address offset: 0x08 */
  __vo uint32_t CIR;           /* TODO,     										Address offset: 0x0C */
  __vo uint32_t AHB1RSTR;      /* TODO,     										Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /* TODO,     										Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /* TODO,     										Address offset: 0x18 */
       uint32_t RESERVED0;     /* Reserved, 0x1C                                                       */
  __vo uint32_t APB1RSTR;      /* TODO,     										Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /* TODO,     										Address offset: 0x24 */
       uint32_t RESERVED1[2];  /* Reserved, 0x28-0x2C                                                  */
  __vo uint32_t AHB1ENR;       /* TODO,     										Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /* TODO,     										Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /* TODO,     										Address offset: 0x38 */
       uint32_t RESERVED2;     /* Reserved, 0x3C                                                       */
  __vo uint32_t APB1ENR;       /* TODO,     										Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /* TODO,     										Address offset: 0x44 */
       uint32_t RESERVED3[2];  /* Reserved, 0x48-0x4C                                                  */
  __vo uint32_t AHB1LPENR;     /* TODO,     										Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /* TODO,     										Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /* TODO,     										Address offset: 0x58 */
       uint32_t RESERVED4;     /* Reserved, 0x5C                                                       */
  __vo uint32_t APB1LPENR;     /* TODO,     										Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /* RTODO,     										Address offset: 0x64 */
       uint32_t RESERVED5[2];  /* Reserved, 0x68-0x6C                                                  */
  __vo uint32_t BDCR;          /* TODO,     										Address offset: 0x70 */
  __vo uint32_t CSR;           /* TODO,     										Address offset: 0x74 */
       uint32_t RESERVED6[2];  /* Reserved, 0x78-0x7C                                                  */
  __vo uint32_t SSCGR;         /* TODO,     										Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /* TODO,     										Address offset: 0x84 */
  __vo uint32_t PLLSAICFGR;    /* TODO,     										Address offset: 0x88 */
  __vo uint32_t DCKCFGR;       /* TODO,     										Address offset: 0x8C */
  __vo uint32_t CKGATENR;      /* TODO,     										Address offset: 0x90 */
  __vo uint32_t DCKCFGR2;      /* TODO,     										Address offset: 0x94 */

} RCC_RegDef_t;

/********************************************************************
 * EXTI register definition structure
 *******************************************************************/

typedef struct
{
	__vo uint32_t IMR;		/* Interrupt mask register (EXTI_IMR), 		   Address Offset = 0x00 */
	__vo uint32_t EMR;		/* Event mask register (EXTI_EMR), 		        Address Offset = 0x04 */
	__vo uint32_t RTSR;		/* Rising trigger selection register (EXTI_RTSR),  Address Offset = 0x08 */
	__vo uint32_t FTSR;		/* Falling trigger selection register (EXTI_FTSR), Address Offset = 0x0C */
	__vo uint32_t SWIER;	/* Software interrupt event register (EXTI_SWIER), Address Offset = 0x10 */
	__vo uint32_t PR;		/* Pending register (EXTI_PR),                     Address Offset = 0x14 */

}EXTI_RegDef_t;

/********************************************************************
 * SYSCFG register definition structure
 *******************************************************************/

typedef struct
{
    __vo uint32_t MEMRMP;        /* Offset: 0x00 */
    __vo uint32_t PMC;           /* Offset: 0x04 */
    __vo uint32_t EXTICR[4];     /* Offset: 0x08 - 0x14 */
    __vo uint32_t CMPCR;         /* Offset: 0x20 */
    uint32_t RESERVED2[2];       /* RESERVED	Address Offset = 0x24 to 0x28 */
    __vo uint32_t CFGR;          /* Offset: 0x2C */
    
}SYSCFG_RegDef_t;

/********************************************************************
 * USART Register Definition structure
 *******************************************************************/

typedef struct
{
	__vo uint32_t SR;		  /* USART Status register ,   Address Offset = 0x00 */
	__vo uint32_t DR;		  /* USART Data register,      Address Offset = 0x04 */
	__vo uint32_t BRR;		  /* USART Baud rate register, Address Offset = 0x08 */
	__vo uint32_t CR1;		  /* USART Control register 1, Address Offset = 0x0C */
	__vo uint32_t CR2;		  /* USART Control register 2, Address Offset = 0x10 */
	__vo uint32_t CR3;		  /* USART Control register 3, Address Offset = 0x14 */
	__vo uint32_t GTPR;		  /* USART Guard time and prescaler register, Address Offset = 0x18 */

}USART_RegDef_t;

/********************************************************************
 * SPI Register Definition structure
 *******************************************************************/

typedef struct
{
    __vo uint32_t CR1;        /* SPI control register 1 (SPI_CR1),              Offset : 0x00 */
    __vo uint32_t CR2;        /* SPI control register 2 (SPI_CR2),              Offset : 0x04 */
    __vo uint32_t SR;         /* SPI status register (SPI_SR),                  Offset : 0x08 */
    __vo uint32_t DR;         /* SPI data register (SPI_DR),                    Offset : 0x0C */
    __vo uint32_t CRCPR;      /* SPI CRC polynomial register (SPI_CRCPR),       Offset : 0x10 */
    __vo uint32_t RXCRCR;     /* SPI RX CRC register (SPI_RXCRCR),              Offset : 0x14 */
    __vo uint32_t TXCRCR;     /* SPI TX CRC register (SPI_TXCRCR),              Offset : 0x18 */
    __vo uint32_t I2SCFGR;    /* SPI_I2S configuration register (SPI_I2SCFGR),  Offset : 0x1C */
    __vo uint32_t I2SPR;      /* SPI_I2S prescaler register (SPI_I2SPR),        Offset : 0x20 */

}SPI_RegDef_t;

/********************************************************************
 * I2C Register Definition structure
 *******************************************************************/

typedef struct
{
  __vo uint32_t CR1;        /* I2C control register 1 (I2C_CR1),         Address offset: 0x00 */
  __vo uint32_t CR2;        /* I2C control register 2 (I2C_CR2),     	   Address offset: 0x04 */
  __vo uint32_t OAR1;       /* I2C own address register 1 (I2C_OAR1),    Address offset: 0x08 */
  __vo uint32_t OAR2;       /* I2C own address register 2 (I2C_OAR2),    Address offset: 0x0C */
  __vo uint32_t DR;         /* I2C data register (I2C_DR),     		   Address offset: 0x10 */
  __vo uint32_t SR1;        /* I2C status register 1 (I2C_SR1),     	   Address offset: 0x14 */
  __vo uint32_t SR2;        /* I2C status register 2 (I2C_SR2),     	   Address offset: 0x18 */
  __vo uint32_t CCR;        /* I2C clock control register (I2C_CCR),     Address offset: 0x1C */
  __vo uint32_t TRISE;      /* I2C TRISE register (I2C_TRISE),     	   Address offset: 0x20 */
  __vo uint32_t FLTR;       /* I2C FLTR register (I2C_FLTR),     	   Address offset: 0x24 */
}I2C_RegDef_t;

/********************************************************************
 * ADC Register Definition structure
 *******************************************************************/
typedef struct
{
    __vo uint32_t SR;          /* ADC status register(ADC_SR)                             Offset: 0x00 */
    __vo uint32_t CR1;         /* ADC control register 1(ADC_CR1)                         Offset: 0x04 */
    __vo uint32_t CR2;         /* ADC control register 2 (ADC_CR2)                        Offset: 0x08 */
    __vo uint32_t SMPR1;       /* ADC sample time register 1 (ADC_SMPR1)                  Offset: 0x0C */
    __vo uint32_t SMPR2;       /* ADC sample time register 2 (ADC_SMPR2)                  Offset: 0x10 */
    __vo uint32_t JOFR1;       /* ADC injected channel data offset register 1 (ADC_JOFRx) Offset: 0x14 */
    __vo uint32_t JOFR2;       /* ADC injected channel data offset register 2 (ADC_JOFRx) Offset: 0x18 */
    __vo uint32_t JOFR3;       /* ADC injected channel data offset register 3 (ADC_JOFRx) Offset: 0x1C */
    __vo uint32_t JOFR4;       /* ADC injected channel data offset register 4 (ADC_JOFRx) Offset: 0x20 */
    __vo uint32_t HTR;         /* ADC watchdog higher threshold register (ADC_HTR)        Offset: 0x24 */
    __vo uint32_t LTR;         /* ADC watchdog lower threshold register (ADC_LTR)         Offset: 0x28 */
    __vo uint32_t SQR1;        /* ADC regular sequence register 1 (ADC_SQR1)              Offset: 0x2C */
    __vo uint32_t SQR2;        /* ADC regular sequence register 2 (ADC_SQR2)              Offset: 0x30 */
    __vo uint32_t SQR3;        /* ADC regular sequence register 3 (ADC_SQR3)              Offset: 0x34 */
    __vo uint32_t JSQR;        /* ADC injected sequence register (ADC_JSQR)               Offset: 0x38 */
    __vo uint32_t JDR1;        /* ADC injected data register 1 (ADC_JDRx) (x= 1..4)       Offset: 0x3C */
    __vo uint32_t JDR2;        /* ADC injected data register 2 (ADC_JDRx) (x= 1..4)       Offset: 0x40 */
    __vo uint32_t JDR3;        /* ADC injected data register 3 (ADC_JDRx) (x= 1..4)       Offset: 0x44 */
    __vo uint32_t JDR4;        /* ADC injected data register 4 (ADC_JDRx) (x= 1..4)       Offset: 0x48 */
    __vo uint32_t DR;          /* ADC regular data register (ADC_DR)                      Offset: 0x4C */

}ADC_RegDef_t;

/*
 * ADC Common Register Definition Structure
 */
typedef struct
{
    volatile uint32_t CSR;     /* ADC Common status register (ADC_CSR)                                 Offset: 0x00 */
    volatile uint32_t CCR;     /* ADC common control register (ADC_CCR)                                Offset: 0x04 */
    volatile uint32_t CDR;     /* ADC common regular data register for dual and triple modes(ADC_CDR)  Offset: 0x08 */

}ADC_Common_RegDef_t;

/********************************************************************
 * peripheral definitions ( Peripheral base addresses typecasted to xxx_RegDef_t)
 *******************************************************************/
/* GPIOx Peripheral Definitions*/
#define GPIOA  				((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB  				((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC  				((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD  				((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE  				((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF  				((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG  				((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH  				((GPIO_RegDef_t*)GPIOH_BASEADDR)

/* RCC Peripheral Definitions*/
#define RCC 				     ((RCC_RegDef_t*)RCC_BASEADDR)

/* EXTI and SYSCFG Peripheral Definitions*/
#define EXTI                       ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG                     ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)  

/* USARTx Peripheral Definitions*/
#define USART1		               ((USART_RegDef_t*) USART1_BASEADDR)
#define USART2		               ((USART_RegDef_t*) USART2_BASEADDR)
#define USART3		               ((USART_RegDef_t*) USART3_BASEADDR)
#define UART4		               ((USART_RegDef_t*) UART4_BASEADDR)
#define UART5		               ((USART_RegDef_t*) UART5_BASEADDR)
#define USART6		               ((USART_RegDef_t*) USART6_BASEADDR)

/* SPIx Peripheral Definitions*/
#define SPI1                       ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2                       ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3                       ((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4                       ((SPI_RegDef_t*)SPI4_BASEADDR)

/* I2Cx Peripheral Definitions*/
#define I2C1  				     ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2  				     ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3  				     ((I2C_RegDef_t*)I2C3_BASEADDR)

/* ADCx Peripheral Definitions*/
#define ADC1                       ((ADC_RegDef_t*)ADC1_BASEADDR)
#define ADC2                       ((ADC_RegDef_t*)ADC2_BASEADDR)
#define ADC3                       ((ADC_RegDef_t*)ADC3_BASEADDR)
#define ADC_COMMON                 ((ADC_Common_RegDef_t*)ADC_COMMON_BASEADDR)

/********************************************************************
 * Clock Enable Macros for GPIOx peripherals
 ********************************************************************/
#define GPIOA_PCLK_EN()		( RCC->AHB1ENR |= (1 << 0) )
#define GPIOB_PCLK_EN()		( RCC->AHB1ENR |= (1 << 1) )
#define GPIOC_PCLK_EN()		( RCC->AHB1ENR |= (1 << 2) )
#define GPIOD_PCLK_EN()		( RCC->AHB1ENR |= (1 << 3) )
#define GPIOE_PCLK_EN()		( RCC->AHB1ENR |= (1 << 4) )
#define GPIOF_PCLK_EN()		( RCC->AHB1ENR |= (1 << 5) )
#define GPIOG_PCLK_EN()		( RCC->AHB1ENR |= (1 << 6) )
#define GPIOH_PCLK_EN()		( RCC->AHB1ENR |= (1 << 7) )

/********************************************************************
 * Clock Enable Macros for SYSCFG Peripherals
********************************************************************/
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))

/********************************************************************
 * Clock Enable Macros for USARTx peripherals
 ********************************************************************/
#define USART1_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()		(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()		(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()		(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))

/********************************************************************
 * Clock Enable Macros for SPIx peripherals
 ********************************************************************/
#define SPI1_PCLK_EN()        (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()        (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()        (RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()        (RCC->APB2ENR |= (1 << 13))

/********************************************************************
 * Clock Enable Macros for I2Cx peripherals
 ********************************************************************/
#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))

/********************************************************************
 * Clock Enable Macros for ADCx peripherals
 ********************************************************************/
#define ADC1_PCLK_EN()		(RCC->APB2ENR |= (1 << 8))
#define ADC2_PCLK_EN()		(RCC->APB2ENR |= (1 << 9))
#define ADC3_PCLK_EN()		(RCC->APB2ENR |= (1 << 10))


/********************************************************************
 * Clock Disable Macros for GPIOx peripherals
 ********************************************************************/
#define GPIOA_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 0) )
#define GPIOB_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 1) )
#define GPIOC_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 2) )
#define GPIOD_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 3) )
#define GPIOE_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 4) )
#define GPIOF_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 5) )
#define GPIOG_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 6) )
#define GPIOH_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 7) )

/********************************************************************
 * Clock Disable Macros for SYSCFG Peripherals
********************************************************************/
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))

/********************************************************************
 * Clock Disable Macros for USARTx Peripherals
 ********************************************************************/
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))

/********************************************************************
 * Clock Disable Macros for SPIx Peripherals
 ********************************************************************/
#define SPI1_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << 12) )
#define SPI2_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 14) )
#define SPI3_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << 15) )
#define SPI4_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << 13) )

/********************************************************************
 * Clock Disable Macros for I2Cx Peripherals
 ********************************************************************/
#define I2C1_PCLK_DI()	   (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()	   (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()	   (RCC->APB1ENR &= ~(1 << 23))

/********************************************************************
 * Clock Disable Macros for ADCx Peripherals
 ********************************************************************/
#define ADC1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 8))
#define ADC2_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 9))
#define ADC3_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 10))


/********************************************************************
 * Macros to reset GPIOx peripherals
 ********************************************************************/
#define GPIOA_REG_RESET()			do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

/********************************************************************
 * Macros to reset USARTx peripherals
 ********************************************************************/
#define USART1_REG_RESET()              do{ (RCC->APB2RSTR |= (1 << 4));  (RCC->APB2RSTR &= ~(1 << 4)); }while(0)
#define USART2_REG_RESET()              do{ (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); }while(0)
#define USART3_REG_RESET()              do{ (RCC->APB1RSTR |= (1 << 18)); (RCC->APB1RSTR &= ~(1 << 18)); }while(0)
#define UART4_REG_RESET()               do{ (RCC->APB1RSTR |= (1 << 19)); (RCC->APB1RSTR &= ~(1 << 19)); }while(0)
#define UART5_REG_RESET()               do{ (RCC->APB1RSTR |= (1 << 20)); (RCC->APB1RSTR &= ~(1 << 20)); }while(0)
#define USART6_REG_RESET()              do{ (RCC->APB2RSTR |= (1 << 5));  (RCC->APB2RSTR &= ~(1 << 5)); }while(0)

/********************************************************************
 * Macros to reset SPIx peripherals
 ********************************************************************/
#define SPI1_REG_RESET()               do{ (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()               do{ (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()               do{ (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)
#define SPI4_REG_RESET()               do{ (RCC->APB2RSTR |= (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13)); }while(0)

/********************************************************************
 * Macros to reset SPIx peripherals
 ********************************************************************/
#define I2C1_REG_RESET()              do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()              do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()              do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)

/********************************************************************
 * Macros to reset ADCx peripherals
 ********************************************************************/
#define ADC1_REG_RESET()             do{ (RCC->APB2RSTR |=  (1 << 8)); (RCC->APB2RSTR &= ~(1 << 8)); }while(0)
#define ADC2_REG_RESET()             do{ (RCC->APB2RSTR |=  (1 << 9)); (RCC->APB2RSTR &= ~(1 << 9)); }while(0)
#define ADC3_REG_RESET()             do{ (RCC->APB2RSTR |=  (1 << 10)); (RCC->APB2RSTR &= ~(1 << 10)); }while(0)

/********************************************************************
 * USART CR1 Bit Definitions
 ********************************************************************/
#define USART_CR1_SBK          0U
#define USART_CR1_RWU          1U
#define USART_CR1_RE           2U
#define USART_CR1_TE           3U
#define USART_CR1_IDLEIE       4U
#define USART_CR1_RXNEIE       5U
#define USART_CR1_TCIE         6U
#define USART_CR1_TXEIE        7U
#define USART_CR1_PEIE         8U
#define USART_CR1_PS           9U
#define USART_CR1_PCE          10U
#define USART_CR1_WAKE         11U
#define USART_CR1_M            12U
#define USART_CR1_UE           13U
#define USART_CR1_OVER8        15U

/********************************************************************
 * USART CR2 Bit Definitions
 ********************************************************************/
#define USART_CR2_STOP         12U

/********************************************************************
 * USART CR3 Bit Definitions
 ********************************************************************/
#define USART_CR3_RTSE         8U
#define USART_CR3_CTSE         9U
#define USART_CR3_DMAT         7U
#define USART_CR3_DMAR         6U

/********************************************************************
 * USART SR Bit Definitions
 ********************************************************************/
#define USART_SR_PE            0U
#define USART_SR_FE            1U
#define USART_SR_NF            2U
#define USART_SR_ORE           3U
#define USART_SR_IDLE          4U
#define USART_SR_RXNE          5U
#define USART_SR_TC            6U
#define USART_SR_TXE           7U
#define USART_SR_LBD           8U
#define USART_SR_CTS           9U

/********************************************************************
 * SPI CR1 Bit Definitions
 ********************************************************************/
#define SPI_CR1_CPHA           0U
#define SPI_CR1_CPOL           1U
#define SPI_CR1_MSTR           2U
#define SPI_CR1_BR             3U
#define SPI_CR1_SPE            6U
#define SPI_CR1_LSBFIRST       7U
#define SPI_CR1_SSI            8U
#define SPI_CR1_SSM            9U
#define SPI_CR1_RXONLY         10U
#define SPI_CR1_DFF            11U
#define SPI_CR1_CRCNEXT        12U
#define SPI_CR1_CRCEN          13U
#define SPI_CR1_BIDIOE         14U
#define SPI_CR1_BIDIMODE       15U

/********************************************************************
 * SPI CR2 Bit Definitions
 ********************************************************************/
#define SPI_CR2_RXDMAEN        0U
#define SPI_CR2_TXDMAEN        1U
#define SPI_CR2_SSOE           2U
#define SPI_CR2_ERRIE          5U
#define SPI_CR2_RXNEIE         6U
#define SPI_CR2_TXEIE          7U

/********************************************************************
 * SPI SR Bit Definitions
 ********************************************************************/
#define SPI_SR_RXNE            0U
#define SPI_SR_TXE             1U
#define SPI_SR_CHSIDE          2U
#define SPI_SR_UDR             3U
#define SPI_SR_CRCERR          4U
#define SPI_SR_MODF            5U
#define SPI_SR_OVR             6U
#define SPI_SR_BSY             7U
#define SPI_SR_FRE             8U

/********************************************************************
 * I2C_CR1 Bit Definitions
 ********************************************************************/
#define I2C_CR1_PE            0U
#define I2C_CR1_SMBUS         1U
#define I2C_CR1_SMBTYPE       3U
#define I2C_CR1_ENARP         4U
#define I2C_CR1_ENPEC         5U
#define I2C_CR1_ENGC          6U
#define I2C_CR1_NOSTRETCH     7U
#define I2C_CR1_START         8U
#define I2C_CR1_STOP          9U
#define I2C_CR1_ACK           10U
#define I2C_CR1_POS           11U
#define I2C_CR1_PEC           12U
#define I2C_CR1_ALERT         13U
#define I2C_CR1_SWRST         15U

/********************************************************************
 * I2C_CR2 Bit Definitions
 ********************************************************************/
#define I2C_CR2_FREQ          0U    // Bits [5:0]
#define I2C_CR2_ITERREN       8U
#define I2C_CR2_ITEVTEN       9U
#define I2C_CR2_ITBUFEN       10U
#define I2C_CR2_DMAEN         11U
#define I2C_CR2_LAST          12U

/********************************************************************
 * I2C_SR1 Bit Position Definitions
 ********************************************************************/
#define I2C_SR1_SB            0U
#define I2C_SR1_ADDR          1U
#define I2C_SR1_BTF           2U
#define I2C_SR1_ADD10         3U
#define I2C_SR1_STOPF         4U
#define I2C_SR1_RXNE          6U
#define I2C_SR1_TXE           7U
#define I2C_SR1_BERR          8U
#define I2C_SR1_ARLO          9U
#define I2C_SR1_AF            10U
#define I2C_SR1_OVR           11U
#define I2C_SR1_PECERR        12U
#define I2C_SR1_TIMEOUT       14U
#define I2C_SR1_SMBALERT      15U

/********************************************************************
 * I2C_OAR1 Bit Position Definitions
 ********************************************************************/
#define I2C_OAR1_ADD0         0U
#define I2C_OAR1_ADD71        1U      // Address bits [7:1]
#define I2C_OAR1_ADDMODE      15U

/********************************************************************
 * I2C_CCR Bit Position Definitions
 ********************************************************************/
#define I2C_CCR_CCR           0U      // Bits [11:0]
#define I2C_CCR_DUTY          14U
#define I2C_CCR_FS            15U

/********************************************************************
 * ADC_CR1 Bit Position Definitions
 ********************************************************************/
#define ADC_CR1_AWDCH          0U
#define ADC_CR1_EOCIE          5U
#define ADC_CR1_AWDIE          6U
#define ADC_CR1_JEOCIE         7U
#define ADC_CR1_SCAN           8U
#define ADC_CR1_AWDSGL         9U
#define ADC_CR1_JAUTO          10U
#define ADC_CR1_DISCEN         11U
#define ADC_CR1_JDISCEN        12U
#define ADC_CR1_DISCNUM        13U
#define ADC_CR1_JAWDEN         22U
#define ADC_CR1_AWDEN          23U
#define ADC_CR1_RES            24U
#define ADC_CR1_OVRIE          26U

/********************************************************************
 * ADC_CR2 Bit Position Definitions
 ********************************************************************/
#define ADC_CR2_ADON           0U
#define ADC_CR2_CONT           1U
#define ADC_CR2_DMA            8U
#define ADC_CR2_DDS            9U
#define ADC_CR2_EOCS           10U
#define ADC_CR2_ALIGN          11U
#define ADC_CR2_JEXTSEL        16U
#define ADC_CR2_JEXTEN         20U
#define ADC_CR2_JSWSTART       22U
#define ADC_CR2_EXTSEL         24U
#define ADC_CR2_EXTEN          28U
#define ADC_CR2_SWSTART        30U

/********************************************************************
 * ADC_SR Bit Position Definitions
 ********************************************************************/
#define ADC_SR_AWD             0U
#define ADC_SR_EOC             1U
#define ADC_SR_JEOC            2U
#define ADC_SR_JSTRT           3U
#define ADC_SR_STRT            4U
#define ADC_SR_OVR             5U

/********************************************************************
 * ADC_SMPR1 Bit Position Definitions
 ********************************************************************/
#define ADC_SMPR1_SMP10        0U
#define ADC_SMPR1_SMP11        3U
#define ADC_SMPR1_SMP12        6U
#define ADC_SMPR1_SMP13        9U
#define ADC_SMPR1_SMP14        12U
#define ADC_SMPR1_SMP15        15U
#define ADC_SMPR1_SMP16        18U
#define ADC_SMPR1_SMP17        21U
#define ADC_SMPR1_SMP18        24U

/********************************************************************
 * ADC_SMPR2 Bit Position Definitions
 ********************************************************************/
#define ADC_SMPR2_SMP0         0U
#define ADC_SMPR2_SMP1         3U
#define ADC_SMPR2_SMP2         6U
#define ADC_SMPR2_SMP3         9U
#define ADC_SMPR2_SMP4         12U
#define ADC_SMPR2_SMP5         15U
#define ADC_SMPR2_SMP6         18U
#define ADC_SMPR2_SMP7         21U
#define ADC_SMPR2_SMP8         24U
#define ADC_SMPR2_SMP9         27U

/********************************************************************
 * ADC_SQR1 Bit Position Definitions
 ********************************************************************/
#define ADC_SQR1_SQ13          0U
#define ADC_SQR1_SQ14          5U
#define ADC_SQR1_SQ15          10U
#define ADC_SQR1_SQ16          15U
#define ADC_SQR1_L             20U

/********************************************************************
 * ADC_SQR2 Bit Position Definitions
 ********************************************************************/
#define ADC_SQR2_SQ7           0U
#define ADC_SQR2_SQ8           5U
#define ADC_SQR2_SQ9           10U
#define ADC_SQR2_SQ10          15U
#define ADC_SQR2_SQ11          20U
#define ADC_SQR2_SQ12          25U

/********************************************************************
 * ADC_SQR3 Bit Position Definitions
 ********************************************************************/
#define ADC_SQR3_SQ1           0U
#define ADC_SQR3_SQ2           5U
#define ADC_SQR3_SQ3           10U
#define ADC_SQR3_SQ4           15U
#define ADC_SQR3_SQ5           20U
#define ADC_SQR3_SQ6           25U

/********************************************************************
 * ADC_CCR Bit Position Definitions
 ********************************************************************/
#define ADC_CCR_MULTI          0U
#define ADC_CCR_DELAY          8U
#define ADC_CCR_DDS            13U
#define ADC_CCR_DMA            14U
#define ADC_CCR_ADCPRE         16U
#define ADC_CCR_VBATE          22U
#define ADC_CCR_TSVREFE        23U

/********************************************************************
 * Macros for GPIO IRQ Numbers
 ********************************************************************/
#define IRQ_NO_EXTI0           6U
#define IRQ_NO_EXTI1           7U
#define IRQ_NO_EXTI2           8U
#define IRQ_NO_EXTI3           9U
#define IRQ_NO_EXTI4           10U
#define IRQ_NO_EXTI9_5         23U
#define IRQ_NO_EXTI15_10       40U

/********************************************************************
 * Macros for USART IRQ Numbers
 ********************************************************************/
#define IRQ_NO_USART1          37U
#define IRQ_NO_USART2          38U
#define IRQ_NO_USART3          39U
#define IRQ_NO_UART4           52U
#define IRQ_NO_UART5           53U
#define IRQ_NO_USART6          71U

/********************************************************************
 * Macros for SPI IRQ Numbers
 ********************************************************************/
#define SPI1_IRQ_NO            35U
#define SPI2_IRQ_NO            36U
#define SPI3_IRQ_NO            51U
#define SPI4_IRQ_NO            84U

/********************************************************************
 * Macro for ADC IRQ Numbers
 ********************************************************************/
#define ADC_IRQ_NO            18U


/* Enable and Disable Macros */
#define ENABLE                 1U
#define DISABLE                0U

/* Flag Set and Reset Macros */
#define FLAG_SET               ENABLE
#define FLAG_RESET             DISABLE

/* Header Files */
#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_rcc_driver.h"
#include "stm32f446xx_usart_driver.h"


/************************ END: MCU Specific Details ************************/

#endif