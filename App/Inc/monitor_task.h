/**
 * @file    monitor_task.h
 * @author  Sunil Sutar
 * @brief   System health monitoring interface.
 *
 * @details
 * Provides the interface for the Monitor Task.
 *
 * The Monitor Task supervises application task health using
 * heartbeat and activity counters.
 *
 * Periodic tasks:
 *      - SensorTask
 *      - ProcessingTask
 *      - DisplayTask
 *
 * Event-driven tasks:
 *      - AlarmTask
 *      - LoggerTask
 *
 * Health states:
 *      - OK
 *      - ACTIVE
 *      - IDLE
 *      - STANDBY
 *      - FAILED
 *      - HEALTHY
 *      - FAULT
 */

#ifndef MONITOR_TASK_H
#define MONITOR_TASK_H

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief System monitoring task.
 *
 * Monitors FreeRTOS heap usage, task stack usage,
 * queue status, and system health.
 *
 * @param pvParameters Task parameter.
 */
void MonitorTask(void *pvParameters);

#endif /* MONITOR_TASK_H */