/**
 * @file    display_task.h
 * @author  Sunil Sutar
 * @brief   Display Task interface.
 *
 * @details
 * Provides the interface for the Display Task.
 *
 * Responsibilities:
 *      - Receive system status
 *      - Display temperature
 *      - Display pressure
 *      - Display voltage
 *      - Display machine status
 *      - Display emergency status
 *      - Display alarm information
 *
 * Current output:
 *      UART-based system status display.
 *
 * Future enhancement:
 *      STM32 16x2 LCD driver.
 *
 * Health monitoring:
 *      DisplayHeartbeat
 */

#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief UART display task.
 *
 * Periodically displays system status,
 * sensor values, and alarm information.
 *
 * @param pvParameters Task parameter.
 */
void DisplayTask(void *pvParameters);

#endif /* DISPLAY_TASK_H */