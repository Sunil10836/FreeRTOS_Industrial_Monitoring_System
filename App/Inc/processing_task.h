/**
 * @file    processing_task.h
 * @author  Sunil Sutar
 * @brief   Processing Task interface.
 *
 * @details
 * Provides the interface for processing sensor data and
 * performing industrial parameter monitoring.
 *
 * Responsibilities:
 *      - Receive sensor data
 *      - Check configured thresholds
 *      - Generate alarm bitmasks
 *      - Detect fault conditions
 *      - Detect system recovery
 *      - Notify Alarm Task
 *      - Send events to Logger Task
 *      - Send status data to Display Task
 *
 * Monitored parameters:
 *      - Temperature
 *      - Pressure
 *      - Voltage
 *
 * Health monitoring:
 *      ProcessingHeartbeat
 */

#ifndef PROCESSING_TASK_H
#define PROCESSING_TASK_H

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Sensor data processing task.
 *
 * Receives sensor data from the Sensor Queue,
 * checks configured limits, and determines
 * whether an abnormal condition or alarm exists.
 *
 * @param pvParameters Task parameter.
 */

void ProcessingTask(void *pvParameters);

#endif /* PROCESSING_TASK_H */