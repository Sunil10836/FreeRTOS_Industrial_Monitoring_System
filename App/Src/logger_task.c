/**
 * @file    logger_task.c
 * @author  Sunil Sutar
 * @brief   Event logging Task implementation.
 *
 * @details
 * Implements the Logger Task for the Industrial Monitoring
 * System.
 *
 * The Logger Task receives event information through a
 * FreeRTOS queue and reports important system events through
 * UART.
 *
 * Logged events may include:
 *      - High temperature
 *      - High pressure
 *      - Low voltage
 *      - Emergency condition
 *      - System recovery
 *
 * FreeRTOS mechanisms:
 *      - Task
 *      - Queue
 *      - Blocking receive
 *
 * Health monitoring:
 *      LoggerActivity is incremented when a logging event
 *      is successfully processed.
 */

#include <stdio.h>
#include "logger_task.h"
#include "app_tasks.h"
#include "logger_event.h"

void LoggerTask(void *pvParameters)
{
    (void)pvParameters;

    LoggerEvent_t event;

    char message[200];

    while (1)
    {
        //APP_UART_Print("[Logger] Task Running\r\n");

        /* Wait for a logging event. */
        if(xQueueReceive(LoggerQueue, &event, portMAX_DELAY) == pdPASS)
        {
            switch (event.eventType)
            {
                case LOGGER_EVENT_INFO:
                    
                    snprintf(message, sizeof(message), 
                        "[LOGGER] INFO\r\n"
                        "Temperature : %.1f C\r\n"
                        "Pressure    : %.1f Bar\r\n"
                        "Voltage     : %.1f V\r\n",
                        event.temperature,
                        event.pressure,
                        event.voltage);

                    break;
                
                case LOGGER_EVENT_HIGH_TEMPERATURE:
                    
                    snprintf(message, sizeof(message),
                        "[LOGGER] HIGH TEMPERATURE\r\n"
                        "Temperature : %.1f C\r\n"
                        "Pressure    : %.1f Bar\r\n"
                        "Voltage     : %.1f V\r\n",
                        event.temperature,
                        event.pressure,
                        event.voltage);

                    break;

                case LOGGER_EVENT_HIGH_PRESSURE:
                    
                    snprintf( message, sizeof(message),
                        "[LOGGER] HIGH PRESSURE\r\n"
                        "Temperature : %.1f C\r\n"
                        "Pressure    : %.1f Bar\r\n"
                        "Voltage     : %.1f V\r\n",
                        event.temperature,
                        event.pressure,
                        event.voltage);

                    break;
                
                case LOGGER_EVENT_LOW_VOLTAGE:

                    snprintf( message, sizeof(message),
                        "[LOGGER] LOW VOLTAGE\r\n"
                        "Temperature : %.1f C\r\n"
                        "Pressure    : %.1f Bar\r\n"
                        "Voltage     : %.1f V\r\n",
                        event.temperature,
                        event.pressure,
                        event.voltage);

                    break;
                
                case LOGGER_EVENT_EMERGENCY:

                    snprintf( message, sizeof(message),
                        "[LOGGER] EMERGENCY\r\n"
                        "Temperature : %.1f C\r\n"
                        "Pressure    : %.1f Bar\r\n"
                        "Voltage     : %.1f V\r\n",
                        event.temperature,
                        event.pressure,
                        event.voltage);

                    break;
                
                case LOGGER_EVENT_RECOVERY:
                    
                    snprintf( message, sizeof(message),
                        "[LOGGER] SYSTEM RECOVERED\r\n"
                        "Temperature : %.1f C\r\n"
                        "Pressure    : %.1f Bar\r\n"
                        "Voltage     : %.1f V\r\n",
                        event.temperature,
                        event.pressure,
                        event.voltage);

                    break;
                
                default:

                    snprintf( message, sizeof(message),
                        "[LOGGER] UNKNOWN EVENT\r\n");

                    break;
            }

            APP_UART_Print(message);

            /* Logger Activity */
            LoggerActivity++;

        }
    }
}