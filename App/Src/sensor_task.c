/**
 * @file    sensor_task.c
 * @author  Sunil Sutar
 * @brief   Sensor Task implementation.
 *
 * @details
 * Implements the periodic Sensor Task used by the
 * Industrial Monitoring System.
 *
 * The task periodically generates/acquires sensor values
 * and sends them to the Processing Task using a FreeRTOS
 * queue.
 *
 * Data monitored:
 *      - Temperature
 *      - Pressure
 *      - Voltage
 *      - Machine status
 *      - Emergency status
 *
 * FreeRTOS mechanisms:
 *      - Task
 *      - Queue
 *      - Task delay
 *
 * Health monitoring:
 *      SensorHeartbeat is incremented after successful
 *      sensor data transmission.
 */

#include "sensor_task.h"
#include "app_tasks.h"

void SensorTask(void *pvParameters)
{
    (void)pvParameters;

    SensorData_t sensorData;
    
    float temperature = 45.0f;
    float pressure = 4.0f;
    float voltage = 12.2f;
    
    while(1)
    {
        /* Update simulated sensor values */
        temperature += 5.0f;
        pressure += 0.5f;
        voltage -= 0.2f;

        /* Restart simulation after reaching high values */
        if (temperature > 90.0f)
        {
            temperature = 45.0f;
        }

        if (pressure > 7.0f)
        {
            pressure = 4.0f;
        }

        if (voltage < 9.5f)
        {
            voltage = 12.2f;
        }

        /* Initial simulated values */
        sensorData.temperature = temperature;
        sensorData.pressure = pressure;
        sensorData.voltage = voltage;

        sensorData.machineRunning = 1U;
        sensorData.emergency = 0U;

        /* Send sensor data to Processing Task */
        if(xQueueSend(SensorQueue, &sensorData, portMAX_DELAY) == pdPASS)
        {
            //APP_UART_Print("[Sensor] Task Running\r\n");

            /* Sensor Task heartbeat
               Sensor data was successfully produced and sent.
            */
            SensorHeartbeat++;
        
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}