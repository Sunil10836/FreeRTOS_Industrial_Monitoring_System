/**
 * @file    alarm_task.c
 * @author  Sunil Sutar
 * @brief   Alarm Task implementation.
 *
 * @details
 * Implements the event-driven Alarm Task.
 *
 * The task remains blocked while waiting for a notification
 * from the Processing Task.
 *
 * Supported alarm conditions:
 *      - High temperature
 *      - High pressure
 *      - Low voltage
 *      - Emergency
 *      - System recovery
 *
 * FreeRTOS mechanisms:
 *      - Task notification
 *      - Blocking task state
 *
 * The task updates AlarmActivity whenever an alarm or recovery
 * notification is received and processed.
 */

#include <stdio.h>
#include "alarm_task.h"
#include "app_tasks.h"

void AlarmTask(void *pvParameters)
{
    (void)pvParameters;

    uint32_t alarmBits;
    char debugMessage[50];

    LED_Off();

    while (1)
    {
        //APP_UART_Print("[Alarm] Waiting for notification...\r\n");

        /* Wait indefinitely for alarm notification */
        if(xTaskNotifyWait(0U, UINT32_MAX, &alarmBits, portMAX_DELAY) == pdTRUE)
        {
            APP_UART_Print("[Alarm] Notification received\r\n");

            /* Debug: show exactly what Alarm Task received */
            snprintf(
                debugMessage,
                sizeof(debugMessage),
                "[Alarm] Notification = 0x%08lX\r\n",
                (unsigned long)alarmBits
            );
            APP_UART_Print(debugMessage);
        
            /* Alarm Activity */
            AlarmActivity++;

            if((alarmBits & ALARM_TEMPERATURE) != 0U)
            {
                LED_On();

                APP_UART_Print("ALARM: High Temperature\r\n");
            }

            if((alarmBits & ALARM_PRESSURE) != 0U)
            {
                LED_On();

                APP_UART_Print("ALARM: High Pressure\r\n");
            }

            if((alarmBits & ALARM_VOLTAGE) != 0U)
            {
                LED_On();
                
                APP_UART_Print("ALARM: Low Voltage\r\n");
            }

            if((alarmBits & ALARM_EMERGENCY) != 0U)
            {
                LED_On();

                APP_UART_Print("ALARM: Emergency Condition\r\n");
            }

            /*-------------------------------------------------
             * Recovery condition
             *-------------------------------------------------*/
            if ((alarmBits & ALARM_RECOVERY) != 0U)
            {
                LED_Off();

                APP_UART_Print("\r\n[SYSTEM RECOVERED]\r\n"
                                "All parameters are within limits\r\n");
            }
            
             APP_UART_Print("====================\r\n");
        }

    }
}