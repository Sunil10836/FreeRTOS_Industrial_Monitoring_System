/**
 * @file    logger_event.h
 * @author  Sunil Sutar
 * @brief   Logger Evets.
 *
 * @details
 *          Logger evets.
 *
 */

#ifndef LOGGER_EVENT_H
#define LOGGER_EVENT_H

#include <stdint.h>

typedef enum
{
    LOGGER_EVENT_INFO = 0,
    LOGGER_EVENT_HIGH_TEMPERATURE,
    LOGGER_EVENT_HIGH_PRESSURE,
    LOGGER_EVENT_LOW_VOLTAGE,
    LOGGER_EVENT_EMERGENCY,
    LOGGER_EVENT_RECOVERY

}LoggerEventType_t;

typedef struct
{
    LoggerEventType_t eventType;

    float temperature;
    float pressure;
    float voltage;

    uint8_t machineRunning;
    uint8_t emergency;

}LoggerEvent_t;

#endif /* LOGGER_EVENT_H */