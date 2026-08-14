
/**
 * @file    app_tasks.h
 * @author  Sunil Sutar
 * @brief   Application task and RTOS resource declarations.
 *
 * @details
 * This file contains declarations for the FreeRTOS application
 * tasks, task handles, queues, heartbeat counters, and activity
 * counters used by the Industrial Monitoring System.
 *
 * Application tasks:
 *      - SensorTask
 *      - ProcessingTask
 *      - AlarmTask
 *      - LoggerTask
 *      - DisplayTask
 *      - MonitorTask
 *
 * RTOS resources:
 *      - Sensor Queue
 *      - Logger Queue
 *      - Display Queue
 *      - Task handles
 *      - Task health counters
 *
 * @note
 * Resource creation and task initialization are performed by
 * App_Init().
 */

#ifndef APP_TASKS_H_
#define APP_TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "led.h"
#include "uart.h"

#include "logger_event.h"
#include "display_data.h"

/*=========================================================
 * Configuration
 *=========================================================*/
#define SENSOR_QUEUE_LENGTH         10U
#define LOGGER_QUEUE_LENGTH         10U
#define DISPLAY_QUEUE_LENGTH        1U

#define SENSOR_TASK_PRIORITY        4U
#define PROCESS_TASK_PRIORITY       3U
#define ALARM_TASK_PRIORITY         3U
#define DISPLAY_TASK_PRIORITY       2U
#define LOGGER_TASK_PRIORITY        2U
#define MONITOR_TASK_PRIORITY       1U

/* Stack depth is specified in WORDS, not bytes */
#define SENSOR_TASK_STACK           256U
#define PROCESS_TASK_STACK          1024U
#define ALARM_TASK_STACK            256U
#define DISPLAY_TASK_STACK          256U
#define LOGGER_TASK_STACK           256U
#define MONITOR_TASK_STACK          256U

/* Threshold Values */
#define TEMP_HIGH_LIMIT             80.0f
#define PRESSURE_HIGH_LIMIT         6.5f
#define VOLTAGE_LOW_LIMIT           10.0f

/* Alarm bit definitions : Used By Alarm Task  */
#define ALARM_TEMPERATURE           (1UL << 0)
#define ALARM_PRESSURE              (1UL << 1)
#define ALARM_VOLTAGE               (1UL << 2)
#define ALARM_EMERGENCY             (1UL << 3)
#define ALARM_RECOVERY              (1UL << 4)

/* task heartbeat bits : Used By Monitor Task */
// #define HEARTBEAT_SENSOR            (1UL << 0)
// #define HEARTBEAT_PROCESSING        (1UL << 1)
// #define HEARTBEAT_ALARM             (1UL << 2)
// #define HEARTBEAT_LOGGER            (1UL << 3)
// #define HEARTBEAT_DISPLAY           (1UL << 4)

/*=========================================================
 * Sensor Data Structure
 *=========================================================*/
typedef struct 
{
    float temperature;
    float pressure;
    float voltage;
    uint8_t machineRunning;
    uint8_t emergency;

}SensorData_t;

/*=========================================================
 * Queues
 *=========================================================*/
extern QueueHandle_t SensorQueue;
extern QueueHandle_t LoggerQueue;
extern QueueHandle_t DisplayQueue;

/*=========================================================
 * Mutex
 *=========================================================*/
extern SemaphoreHandle_t UARTMutex;

//extern TimerHandle_t SamplingTimer;


/*=========================================================
 * Task Handles
 *=========================================================*/
extern TaskHandle_t SensorTaskHandle;
extern TaskHandle_t ProcessingTaskHandle;
extern TaskHandle_t AlarmTaskHandle;
extern TaskHandle_t LoggerTaskHandle;
extern TaskHandle_t DisplayTaskHandle;
extern TaskHandle_t MonitorTaskHandle;

/*=========================================================
 *  Heartbeat Counters
 *=========================================================*/

 extern volatile uint32_t SensorHeartbeat;
extern volatile uint32_t ProcessingHeartbeat;
extern volatile uint32_t DisplayHeartbeat;

/*=========================================================
 * Event-driven Task Activity
 *=========================================================*/

extern volatile uint32_t LoggerActivity;
extern volatile uint32_t AlarmActivity;


/*=========================================================
 * APIs
 *=========================================================*/

void App_Init();

void APP_UART_Print(const char *message);

#endif