
/**
 * @file    sensor_task.h
 * @author  Sunil Sutar
 * @brief   Sensor Task interface for the Industrial Monitoring System.
 *
 * @details
 * This module provides the interface for the Sensor Task.
 *
 * The Sensor Task is responsible for periodically acquiring
 * or generating industrial monitoring parameters and sending
 * the sensor data to the Processing Task through a FreeRTOS
 * queue.
 *
 * Monitored parameters:
 *      - Temperature
 *      - Pressure
 *      - Voltage
 *      - Machine running status
 *      - Emergency status
 *
 * Communication:
 *      SensorTask -> SensorQueue -> ProcessingTask
 *
 * Health Monitoring:
 *      SensorHeartbeat
 *
 * RTOS mechanisms:
 *      - FreeRTOS Task
 *      - FreeRTOS Queue
 *      - Task Delay
 *
 * @note
 * SensorHeartbeat is incremented after sensor data is
 * successfully transmitted to SensorQueue.
 */

#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "FreeRTOS.h"
#include "task.h"



/**
 * @brief Sensor acquisition task.
 *
 * Reads industrial sensor values periodically and
 * sends the collected data to the processing task.
 *
 * @param pvParameters Task parameter.
 */

void SensorTask(void *pvParameters);


#endif /* SENSOR_TASK_H */