/**
 * @file    monitor_task.c
 * @author  Sunil Sutar
 * @brief   System health monitoring Task implementation.
 *
 * @details
 * Implements the Monitor Task for supervising the health
 * of the Industrial Monitoring System.
 *
 * The Monitor Task periodically checks heartbeat/activity
 * counters and determines whether application tasks are
 * making expected progress.
 *
 * Periodic task monitoring:
 *      SensorTask
 *      ProcessingTask
 *      DisplayTask
 *
 * Event-driven task monitoring:
 *      AlarmTask
 *      LoggerTask
 *
 * A task is considered healthy when its progress/activity
 * counter changes during the monitoring interval.
 *
 * The Monitor Task reports:
 *
 *      - Individual task status
 *      - Overall system health
 *
 * @note
 * Event-driven tasks may remain blocked while waiting for
 * events. An idle/standby state is therefore not considered
 * a task failure.
 */

#include <stdio.h>
#include "monitor_task.h"
#include "app_tasks.h"

void MonitorTask(void *pvParameters)
{
    (void)pvParameters;

    /*=================================================
     * Previous values
     *=================================================*/
    uint32_t previousSensorHeartbeat = 0U;
    uint32_t previousProcessingHeartbeat = 0U;
    uint32_t previousDisplayHeartbeat = 0U;

    uint32_t previousLoggerActivity = 0U;
    uint32_t previousAlarmActivity = 0U;

    /*=================================================
     * Current values
     *=================================================*/
    uint32_t currentSensorHeartbeat;
    uint32_t currentProcessingHeartbeat;
    uint32_t currentDisplayHeartbeat;

    uint32_t currentLoggerActivity;
    uint32_t currentAlarmActivity;

    while (1)
    {
        //APP_UART_Print("[Monitor] Task Running\r\n");

        /*=================================================
         * Wait for monitoring period
         *=================================================*/
        vTaskDelay(pdMS_TO_TICKS(3000));

        APP_UART_Print("\r\n[Monitor] Checking system health...\r\n");

        /*=================================================
         * Read current heartbeat counters
         *=================================================*/
        currentSensorHeartbeat = SensorHeartbeat;
        currentProcessingHeartbeat = ProcessingHeartbeat;
        currentDisplayHeartbeat = DisplayHeartbeat;

        currentLoggerActivity = LoggerActivity;
        currentAlarmActivity = AlarmActivity;
        
        /*=================================================
         * Sensor Task
         *=================================================*/
        if(currentSensorHeartbeat != previousSensorHeartbeat)
        {
            APP_UART_Print("[Monitor] Sensor Task       : OK\r\n");
        }
        else
        {
            APP_UART_Print("[Monitor] Sensor Task       : FAILED\r\n");
        }

        /*=================================================
         * Processing Task
         *=================================================*/
        if(currentProcessingHeartbeat != previousProcessingHeartbeat)
        {
            APP_UART_Print("[Monitor] Processing Task   : OK\r\n");
        }
        else
        {
            APP_UART_Print("[Monitor] Processing Task   : FAILED\r\n");
        }

        /*=================================================
         * Display Task
         *=================================================*/
        if(currentDisplayHeartbeat != previousDisplayHeartbeat)
        {
            APP_UART_Print("[Monitor] Display Task      : OK\r\n");
        }
        else
        {
            APP_UART_Print("[Monitor] Display Task      : FAILED\r\n");
        }

        /*=================================================
         * Logger Task
         *=================================================*/
        if(currentLoggerActivity  != previousLoggerActivity)
        {
            APP_UART_Print("[Monitor] Logger Task       : ACTIVE\r\n");
        }
        else
        {
            APP_UART_Print("[Monitor] Logger Task       : IDLE\r\n");
        }

        /*=================================================
         * ALARM TASK
         *=================================================*/
        if(currentAlarmActivity  != previousAlarmActivity)
        {
            APP_UART_Print("[Monitor] Alarm Task        : ACTIVE\r\n");
        }
        else
        {
            APP_UART_Print("[Monitor] Alarm Task        : IDLE\r\n");
        }

        /*=================================================
         * Overall System Health
         *=================================================*/
        if((currentSensorHeartbeat != previousSensorHeartbeat) &&
            (currentProcessingHeartbeat != previousProcessingHeartbeat))
        {
            APP_UART_Print("[Monitor] SYSTEM STATUS     : HEALTHY\r\n");
        }
        else
        {
            APP_UART_Print("[Monitor] SYSTEM STATUS     : FAULT\r\n");
        }

        /*=================================================
         * Save current values
         *=================================================*/
        previousSensorHeartbeat = currentSensorHeartbeat;
        previousProcessingHeartbeat = currentProcessingHeartbeat;
        previousDisplayHeartbeat = currentDisplayHeartbeat;

        previousLoggerActivity = currentLoggerActivity;
        previousAlarmActivity = currentAlarmActivity;
    }
}