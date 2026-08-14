/**
 * @file    display_task.c
 * @author  Sunil Sutar
 * @brief   System status Display Task implementation.
 *
 * @details
 * Implements the Display Task used to present the current
 * industrial system status.
 *
 * The task receives status information and presents:
 *
 *      - Temperature
 *      - Pressure
 *      - Voltage
 *      - Machine status
 *      - Emergency status
 *      - Alarm bitmask
 *
 * Current implementation:
 *      UART-based status output.
 *
 * Future implementation:
 *      STM32 16x2 LCD.
 *
 * FreeRTOS mechanisms:
 *      - Task
 *      - Queue
 *
 * Health monitoring:
 *      DisplayHeartbeat
 */

#include <stdio.h>
#include "display_task.h"
#include "app_tasks.h"
#include "display_data.h"

void DisplayTask(void *pvParameters)
{
    (void)pvParameters;

    DisplayData_t displayData;

    char message[250];

    while (1)
    {
        /*-------------------------------------------------
         * Wait for latest display data
         *-------------------------------------------------*/
        if(xQueueReceive(DisplayQueue, &displayData, portMAX_DELAY) == pdPASS)
        {
            /*-------------------------------------------------
             * Display System Status
             *-------------------------------------------------*/

            snprintf(
                message,
                sizeof(message),

                "\r\n"
                "============== SYSTEM STATUS ==============\r\n"
                "Temperature : %.1f C\r\n"
                "Pressure    : %.1f Bar\r\n"
                "Voltage     : %.1f V\r\n"
                "Machine     : %s\r\n"
                "Emergency   : %s\r\n"
                "Alarm Bits  : 0x%08lX\r\n"
                "============================================\r\n",

                displayData.temperature,
                displayData.pressure,
                displayData.voltage,

                displayData.machineRunning ? "RUNNING" : "STOPPED",
                displayData.emergency ? "YES" : "NO",
                (unsigned long)displayData.alarmBits
            );

            APP_UART_Print(message);

            /* Display Heartbeat */
            DisplayHeartbeat++;

        }
    }
}