/**
 * @file    main.c
 * @author  Sunil Sutar
 * @brief   Application entry point for the FreeRTOS Industrial Monitoring System.
 *
 * @details
 * This application implements a multi-task industrial monitoring system
 * using FreeRTOS on the STM32F446RE microcontroller.
 *
 * The system consists of the following application tasks:
 *
 *      Sensor Task
 *          |
 *          | SensorQueue
 *          v
 *      Processing Task
 *          |
 *          +---------> Alarm Task
 *          |
 *          +---------> Logger Task
 *          |
 *          +---------> Display Task
 *          
 *      Monitor Task
 *          |
 *          +---------> Task Health Monitoring
 *
 * The application demonstrates:
 *
 *      - FreeRTOS task creation and management
 *      - Task priorities and delays
 *      - Inter-task communication using queues
 *      - Task notifications
 *      - Mutex / semaphore based synchronization
 *      - Software timers
 *      - Alarm and recovery handling
 *      - UART-based logging and system status
 *      - Task heartbeat/activity monitoring
 *
 * Hardware:
 *      - STM32 Nucleo-F446RE
 *      - ARM Cortex-M4F
 *
 * Toolchain:
 *      - ARM GNU Toolchain
 *      - GCC
 *      - Make
 *
 * RTOS:
 *      - FreeRTOS
 *
 * @note
 * The application uses a bare-metal STM32 driver layer and FreeRTOS.
*/

#include "stm32f446xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "app_tasks.h"

int main(void)
{
    /*=================================================
    * Hardware initialization
    *=================================================*/
    USART2_Init();
    
    LED_Init();

    /*=================================================
    * Initialize application RTOS objects/tasks
    *=================================================*/
    App_Init();

    /*=================================================
     * Start Scheduler
     *=================================================*/
    vTaskStartScheduler();

    while(1)
    {
        
    }
}
