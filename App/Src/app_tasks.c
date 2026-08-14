
/**
 * @file    sensor_task.h
 * @author  Sunil Sutar
 * @brief   Sensor Task interface.
 *
 * @details
 * Provides the interface for the Sensor Task of the
 * Industrial Monitoring System.
 *
 * The Sensor Task:
 *      - Acquires/generates sensor data
 *      - Updates temperature
 *      - Updates pressure
 *      - Updates voltage
 *      - Updates machine status
 *      - Updates emergency status
 *      - Sends sensor data to the Processing Task
 *
 * Communication:
 *      SensorTask -> SensorQueue -> ProcessingTask
 *
 * Health monitoring:
 *      SensorHeartbeat
 */

#include "app_tasks.h"
#include "sensor_task.h"
#include "processing_task.h"
#include "alarm_task.h"
#include "display_task.h"
#include "logger_task.h"
#include "monitor_task.h"

extern USART_Handle_t UART2Handle;

/*=========================================================
 * RTOS Objects
 *=========================================================*/
QueueHandle_t SensorQueue = NULL;
QueueHandle_t LoggerQueue = NULL;
QueueHandle_t DisplayQueue = NULL;

SemaphoreHandle_t UARTMutex = NULL;
TimerHandle_t SamplingTimer = NULL;

/*=========================================================
 * Task Handles
 *=========================================================*/
TaskHandle_t SensorTaskHandle = NULL;
TaskHandle_t ProcessingTaskHandle = NULL;
TaskHandle_t DisplayTaskHandle = NULL;
TaskHandle_t AlarmTaskHandle = NULL;
TaskHandle_t LoggerTaskHandle = NULL;
TaskHandle_t MonitorTaskHandle = NULL;

/*=========================================================
 * heartbeat counters
 *=========================================================*/
volatile uint32_t SensorHeartbeat = 0U;
volatile uint32_t ProcessingHeartbeat = 0U;
volatile uint32_t DisplayHeartbeat = 0U;

volatile uint32_t LoggerActivity = 0U;
volatile uint32_t AlarmActivity = 0U;

/*=========================================================
 * Software Timer Callback
 *=========================================================*/
static void SamplingTimerCallback(TimerHandle_t xTimer)
{
    (void)xTimer;


}

/*=========================================================
 * FreeRTOS App Initialization
 *=========================================================*/
void App_Init()
{
    BaseType_t status;

    /*-----------------------------------------------------
     * Create Sensor Queue
     *-----------------------------------------------------*/
    SensorQueue = xQueueCreate(SENSOR_QUEUE_LENGTH, sizeof(SensorData_t));

    if(SensorQueue == NULL)
    {
        /* Queue creation failed */
        APP_UART_Print("[ERROR] Sensor Queue creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Create Logger Queue
     *-----------------------------------------------------*/
    LoggerQueue = xQueueCreate(LOGGER_QUEUE_LENGTH, sizeof(LoggerEvent_t));

    if(LoggerQueue == NULL)
    {
        /* Queue creation failed */
        APP_UART_Print("[ERROR] Logger Queue creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Create Display Queue
     *-----------------------------------------------------*/
    DisplayQueue = xQueueCreate(DISPLAY_QUEUE_LENGTH, sizeof(DisplayData_t));

    if(DisplayQueue == NULL)
    {
        /* Queue creation failed */
        APP_UART_Print("[ERROR] Display Queue creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Create UART Mutex
     *-----------------------------------------------------*/
    UARTMutex = xSemaphoreCreateMutex();

    if(UARTMutex == NULL)
    {
        /* Mutex creation failed */
        APP_UART_Print("[ERROR] Mutex creation failed\r\n");
    }

    /*-----------------------------------------------------
     * Create Software Timer
     *-----------------------------------------------------*/
    SamplingTimer = xTimerCreate("Sampling", pdMS_TO_TICKS(500), pdTRUE, NULL, SamplingTimerCallback);

    if(SamplingTimer == NULL)
    {
        /* Timer creation failed */
        APP_UART_Print("[ERROR] Timer creation failed\r\n");
    }

    /*-----------------------------------------------------
     * Create Sensor Task
     *-----------------------------------------------------*/
    status = xTaskCreate(SensorTask, "Sensor", SENSOR_TASK_STACK, NULL, SENSOR_TASK_PRIORITY, &SensorTaskHandle);

    if(status != pdPASS)
    {
        /* Task Creation Failed */
        APP_UART_Print("[ERROR] Sensor Task creation failed\r\n");
    }

    /*-----------------------------------------------------
     * Create Processing Task
     *-----------------------------------------------------*/
    status = xTaskCreate(ProcessingTask, "Process", PROCESS_TASK_STACK, NULL, PROCESS_TASK_PRIORITY, &ProcessingTaskHandle);

    if(status != pdPASS)
    {
        /* Task Creation Failed */
        APP_UART_Print("[ERROR] Processing Task creation failed\r\n");
        
        while(1);
    }

    /*-----------------------------------------------------
     * Create Alarm Task
     *-----------------------------------------------------*/
    status = xTaskCreate(AlarmTask, "Alarm", ALARM_TASK_STACK, NULL, ALARM_TASK_PRIORITY, &AlarmTaskHandle);

    if(status != pdPASS)
    {
        /* Task Creation Failed */
        APP_UART_Print("[ERROR] Alarm Task creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Create Logger Task
     *-----------------------------------------------------*/
    status = xTaskCreate(LoggerTask, "Logger", LOGGER_TASK_STACK, NULL, LOGGER_TASK_PRIORITY, &LoggerTaskHandle);

    if(status != pdPASS)
    {
        /* Task Creation Failed */
        APP_UART_Print("[ERROR] Logger Task creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Create Display Task
     *-----------------------------------------------------*/
    status = xTaskCreate(DisplayTask, "Display", DISPLAY_TASK_STACK, NULL, DISPLAY_TASK_PRIORITY, &DisplayTaskHandle);

    if(status != pdPASS)
    {
        /* Task Creation Failed */
        APP_UART_Print("[ERROR] Display Task creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Create Monitor Task
     *-----------------------------------------------------*/
    status = xTaskCreate(MonitorTask, "Monitor", MONITOR_TASK_STACK, NULL, MONITOR_TASK_PRIORITY, &MonitorTaskHandle);

    if(status != pdPASS)
    {
        /* Task Creation Failed */
        APP_UART_Print("[ERROR] Monitor Task creation failed\r\n");

        while(1);
    }

    /*-----------------------------------------------------
     * Start Sampling Timer
     *-----------------------------------------------------*/
    if(xTimerStart(SamplingTimer, 0) != pdPASS)
    {
        while(1);
    }

}

void APP_UART_Print(const char *message)
{
    if((message == NULL) || (UARTMutex == NULL))
    {
        return;
    }

    if(xSemaphoreTake(UARTMutex, portMAX_DELAY) == pdTRUE)
    {
        USART_SendString(&UART2Handle, message);

        xSemaphoreGive(UARTMutex);
    }
}