/**
 * @file    logger_task.h
 * @author  Sunil Sutar
 * @brief   Logger Task interface.
 *
 * @details
 * Provides the interface for the event-driven Logger Task.
 *
 * Responsibilities:
 *      - Receive logging events
 *      - Log fault information
 *      - Log alarm information
 *      - Log recovery events
 *      - Output event information through UART
 *
 * Communication:
 *      ProcessingTask -> LoggerQueue -> LoggerTask
 *
 * Health monitoring:
 *      LoggerActivity
 *
 * @note
 * Logger Task may remain blocked/idle when no logging event
 * is available. This is considered normal operation.
 */

#ifndef LOGGER_TASK_H
#define LOGGER_TASK_H

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Data logger task.
 *
 * Stores sensor measurements and system events
 * in a circular buffer for later analysis.
 *
 * @param pvParameters Task parameter.
 */
void LoggerTask(void *pvParameters);

#endif /* LOGGER_TASK_H */