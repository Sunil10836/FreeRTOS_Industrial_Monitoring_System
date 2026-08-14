/**
 * @file    processing_task.c
 * @author  Sunil Sutar
 * @brief   Sensor data processing and fault detection.
 *
 * @details
 * Implements the main decision-making logic of the
 * Industrial Monitoring System.
 *
 * The Processing Task receives sensor data from SensorQueue
 * and compares the measured parameters against configured
 * threshold values.
 *
 * Fault conditions:
 *      - High temperature
 *      - High pressure
 *      - Low voltage
 *      - Emergency condition
 *
 * The detected faults are represented using alarm bitmasks.
 *
 * Inter-task communication:
 *      - SensorQueue
 *      - Alarm Task Notification
 *      - Logger Queue
 *      - Display Queue
 *
 * Recovery:
 *      When all monitored parameters return within limits,
 *      an ALARM_RECOVERY notification is generated.
 *
 * Health monitoring:
 *      ProcessingHeartbeat
 */

#include <stdio.h>
#include "processing_task.h"
#include "app_tasks.h"

static void Logger_SendEvent(const LoggerEvent_t *event);

void ProcessingTask(void *pvParameters)
{
    (void)pvParameters;

    SensorData_t sensorData;

    LoggerEvent_t logEvent;

    DisplayData_t displayData;

    char message[200];

    uint32_t currentAlarmBits = 0U;
    uint32_t previousAlarmBits = 0U;

    while(1)
    {
        /*-------------------------------------------------
         * Wait for Sensor Data
         *-------------------------------------------------*/
        if(xQueueReceive(SensorQueue, &sensorData, portMAX_DELAY) == pdPASS)
        {
            //APP_UART_Print("[Processing] Task Running\r\n");

            /*---------------------------------------------
             * Print sensor data
             *---------------------------------------------*/
            snprintf(
                    message,
                    sizeof(message),
                    "\r\n"
                    "[Processing]\r\n"
                    "Temperature : %.1f C\r\n"
                    "Pressure    : %.1f Bar\r\n"
                    "Voltage     : %.1f V\r\n"
                    "Machine     : %s\r\n"
                    "Emergency   : %s\r\n",
                    sensorData.temperature,
                    sensorData.pressure,
                    sensorData.voltage,
                    sensorData.machineRunning ? "RUNNING" : "STOPPED",
                    sensorData.emergency ? "YES" : "NO"
            );

            APP_UART_Print(message);

            /*---------------------------------------------
             * Fault Detection
             *---------------------------------------------*/                        

            /*  Calculate CURRENT Alarm State */
            currentAlarmBits = 0U;

            /* High Temperature */
            if(sensorData.temperature > TEMP_HIGH_LIMIT)
            {
                currentAlarmBits |= ALARM_TEMPERATURE;
                APP_UART_Print("[DEBUG] Temperature ALARM\r\n");
            }

            /* High Pressure */
            if(sensorData.pressure > PRESSURE_HIGH_LIMIT)
            {
                currentAlarmBits |= ALARM_PRESSURE;
                APP_UART_Print("[DEBUG] Pressure ALARM\r\n");
            }

            /* Low Voltage */
            if(sensorData.voltage < VOLTAGE_LOW_LIMIT)
            {
                currentAlarmBits |= ALARM_VOLTAGE;
                APP_UART_Print("[DEBUG] Voltage ALARM\r\n");
            }

            /* Emergency Condition */
            if(sensorData.emergency != 0U)
            {
                currentAlarmBits |= ALARM_EMERGENCY;
                APP_UART_Print("[DEBUG] Emergency ALARM\r\n");
            }

            /* Processing heartbeat */
            ProcessingHeartbeat++;

            /*-------------------------------------------------
             * Debug Current Alarm State
             *-------------------------------------------------*/
            snprintf(
                message,
                sizeof(message),
                "[DEBUG] T=%.1f P=%.1f V=%.1f -> alarmBits=0x%08lX\r\n",
                sensorData.temperature,
                sensorData.pressure,
                sensorData.voltage,
                (unsigned long)currentAlarmBits);

            APP_UART_Print(message);

            /*-------------------------------------------------
             * Send Latest Data to Display Task
             *-------------------------------------------------*/
            displayData.temperature = sensorData.temperature;
            displayData.pressure = sensorData.pressure;
            displayData.voltage = sensorData.voltage;
            displayData.machineRunning = sensorData.machineRunning;
            displayData.emergency = sensorData.emergency;
            displayData.alarmBits = currentAlarmBits;

            if(DisplayQueue != NULL)
            {
                xQueueOverwrite(DisplayQueue, &displayData);
            }

            /*-------------------------------------------------
             * Prepare Logger Event
             *-------------------------------------------------*/
            logEvent.temperature = sensorData.temperature;
            logEvent.pressure = sensorData.pressure;
            logEvent.voltage = sensorData.voltage;
            logEvent.machineRunning = sensorData.machineRunning;
            logEvent.emergency = sensorData.emergency;

            /*---------------------------------------------
             * Notify Alarm Task
             *---------------------------------------------*/
            /* Alarm State Changed? */
            if (currentAlarmBits != previousAlarmBits)
            {
                /*---------------------------------------------
                 * New Alarm
                 *---------------------------------------------*/
                if(currentAlarmBits != 0U)
                {
                    APP_UART_Print("[Processing] FAULT DETECTED -> Notifying Alarm Task\r\n");
                
                    /*-----------------------------------------
                     * Notify Alarm Task
                     *-----------------------------------------*/
                    if (AlarmTaskHandle != NULL)
                    {
                        APP_UART_Print("[Processing] Before xTaskNotify()\r\n");
                        
                        BaseType_t notifyStatus;

                        notifyStatus = xTaskNotify(AlarmTaskHandle, currentAlarmBits, eSetValueWithOverwrite);
                        
                        if(notifyStatus == pdPASS)
                        {
                            APP_UART_Print("[Processing] xTaskNotify() SUCCESS\r\n");
                        }
                        else
                        {
                            APP_UART_Print("[Processing] xTaskNotify() FAILED\r\n");
                        }
                    }
                    else
                    {
                        APP_UART_Print("[Processing] ERROR: AlarmTaskHandle NULL\r\n");
                    }

                    /*-----------------------------------------
                     * Logger: High Temperature
                     *-----------------------------------------*/
                    if((currentAlarmBits & ALARM_TEMPERATURE) != 0U)
                    {
                        logEvent.eventType = LOGGER_EVENT_HIGH_TEMPERATURE;

                        //xQueueSend(LoggerQueue, &logEvent, 0);
                        Logger_SendEvent(&logEvent);
                    }

                    /*-----------------------------------------
                     * Logger: High Pressure
                     *-----------------------------------------*/
                    if((currentAlarmBits & ALARM_PRESSURE) != 0U)
                    {
                        logEvent.eventType = LOGGER_EVENT_HIGH_PRESSURE;

                        //xQueueSend(LoggerQueue, &logEvent, 0);
                        Logger_SendEvent(&logEvent);
                    }

                    /*-----------------------------------------
                     * Logger: Low Voltage
                     *-----------------------------------------*/
                    if((currentAlarmBits & ALARM_VOLTAGE) != 0U)
                    {
                        logEvent.eventType = LOGGER_EVENT_LOW_VOLTAGE;

                        //xQueueSend(LoggerQueue, &logEvent, 0);
                        Logger_SendEvent(&logEvent);
                    }

                    /*-----------------------------------------
                     * Logger: Emergency
                     *-----------------------------------------*/
                    if((currentAlarmBits & ALARM_EMERGENCY) != 0U)
                    {
                        logEvent.eventType = LOGGER_EVENT_EMERGENCY;

                        //xQueueSend(LoggerQueue, &logEvent, 0);
                        Logger_SendEvent(&logEvent);
                    }

                }
                else
                {
                    /*---------------------------------------------
                    * System Recovery
                    *---------------------------------------------*/
                    APP_UART_Print("[Processing] SYSTEM RECOVERED -> Notifying Alarm Task\r\n");

                    /*-----------------------------------------
                     * Notify Alarm Task
                     *-----------------------------------------*/
                    if (AlarmTaskHandle != NULL)
                    {
                        xTaskNotify(AlarmTaskHandle, ALARM_RECOVERY, eSetValueWithOverwrite);
                    }

                    /*-----------------------------------------
                     * Logger: Recovery Event
                     *-----------------------------------------*/
                    logEvent.eventType = LOGGER_EVENT_RECOVERY;

                    //xQueueSend(LoggerQueue, &logEvent, 0);
                    Logger_SendEvent(&logEvent);
                }
            }

            /*-------------------------------------------------
             * Save Current Alarm State
             *-------------------------------------------------*/
            previousAlarmBits = currentAlarmBits;
        }
    }
}

static void Logger_SendEvent(const LoggerEvent_t *event)
{
    if (LoggerQueue == NULL)
    {
        APP_UART_Print("[LOGGER] ERROR: LoggerQueue is NULL\r\n");

        return;
    }

    if (xQueueSend(LoggerQueue, event, 0U) != pdPASS)
    {
        APP_UART_Print("[LOGGER] ERROR: Failed to send event\r\n");
    }
}