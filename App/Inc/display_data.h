/**
 * @file    display_data.h
 * @author  Sunil Sutar
 * @brief   Display Data.
 *
 * @details
 *      Display Data.
 *
 */

#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H

#include <stdint.h>

typedef struct
{
    float temperature;
    float pressure;
    float voltage;

    uint8_t machineRunning;
    uint8_t emergency;

    uint32_t alarmBits;

} DisplayData_t;

#endif /* DISPLAY_DATA_H */