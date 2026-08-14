# Industrial Monitoring System

A FreeRTOS-based industrial monitoring application developed for the **STM32F446RE**. The project demonstrates practical RTOS concepts including multitasking, queues, task notifications, software timers, synchronization, alarm/recovery handling, event logging, system status reporting, and task health monitoring.

## Project Overview

The system monitors simulated industrial parameters:

- Temperature
- Pressure
- Voltage
- Machine running status
- Emergency status

Sensor data is transferred to a Processing Task through a FreeRTOS queue. The Processing Task checks configurable thresholds, generates alarm bitmasks, notifies the Alarm Task, sends events to the Logger Task, and provides data to the Display Task. A Monitor Task supervises task progress using heartbeat/activity counters.

## System Architecture

```text
                         +----------------------+
                         |      Sensor Task     |
                         | Temperature          |
                         | Pressure             |
                         | Voltage              |
                         | Machine / Emergency  |
                         +----------+-----------+
                                    |
                                    | SensorQueue
                                    v
                         +----------------------+
                         |   Processing Task    |
                         | Threshold Checking   |
                         | Fault Detection      |
                         | Recovery Detection   |
                         +----+---------+-------+
                              |         |
                         Notify|         +----------------+
                              v                          |
                         +---------+                 +---v----+
                         |  Alarm  |                 | Logger |
                         |  Task   |                 |  Task  |
                         +---------+                 +--------+

                         +----------------------+
                         |    Display Task      |
                         | System Status        |
                         +----------------------+

                         +----------------------+
                         |    Monitor Task      |
                         | Heartbeat Counters   |
                         | Activity Monitoring  |
                         | System Health        |
                         +----------------------+
```

## Main Tasks

| Task | Responsibility | Communication / Monitoring |
|---|---|---|
| `SensorTask` | Generate/acquire sensor data | `SensorQueue`, heartbeat |
| `ProcessingTask` | Process data and detect faults | `SensorQueue`, task notification, heartbeat |
| `AlarmTask` | Process alarm/recovery notifications | Task notification, activity counter |
| `LoggerTask` | Log important events | Logger queue, activity counter |
| `DisplayTask` | Present system status | Display queue, heartbeat |
| `MonitorTask` | Monitor application health | Heartbeat/activity counters |

## Sensor Data

```c
typedef struct
{
    float temperature;
    float pressure;
    float voltage;

    uint8_t machineRunning;
    uint8_t emergency;

} SensorData_t;
```

## Alarm Thresholds

```c
#define TEMP_HIGH_LIMIT       80.0f
#define PRESSURE_HIGH_LIMIT    6.5f
#define VOLTAGE_LOW_LIMIT     10.0f
```

### Alarm Bit Definitions

```c
#define ALARM_TEMPERATURE      (1UL << 0)
#define ALARM_PRESSURE         (1UL << 1)
#define ALARM_VOLTAGE          (1UL << 2)
#define ALARM_EMERGENCY        (1UL << 3)
#define ALARM_RECOVERY         (1UL << 4)
```

For example:

```text
0x00000006
```

means:

```text
Bit 1 -> High Pressure
Bit 2 -> Low Voltage
```

## Data Flow

```text
Sensor Task
     |
     | xQueueSend()
     v
SensorQueue
     |
     | xQueueReceive()
     v
Processing Task
     |
     +-------------> Alarm Task
     |
     +-------------> Logger Task
     |
     +-------------> Display Task

Monitor Task
     |
     +---- SensorHeartbeat
     +---- ProcessingHeartbeat
     +---- DisplayHeartbeat
     +---- LoggerActivity
     +---- AlarmActivity
```

## Fault Detection

The Processing Task compares incoming measurements against configured limits.

```text
Temperature > 80.0 C
        |
        v
ALARM_TEMPERATURE

Pressure > 6.5 Bar
        |
        v
ALARM_PRESSURE

Voltage < 10.0 V
        |
        v
ALARM_VOLTAGE
```

Alarm conditions are sent to the Alarm Task:

```c
xTaskNotify(
    AlarmTaskHandle,
    alarmBits,
    eSetBits
);
```

The Alarm Task waits using:

```c
xTaskNotifyWait(
    0U,
    UINT32_MAX,
    &alarmBits,
    portMAX_DELAY
);
```

Example output:

```text
!!! ALARM !!!

[Alarm] Notification = 0x00000002

ALARM: High Pressure
====================
```

## Recovery Detection

When a previously active fault clears and all monitored parameters return within limits, the Processing Task generates:

```c
ALARM_RECOVERY
```

The Alarm Task reports:

```text
[SYSTEM RECOVERED]
All parameters are within limits
```

## Logger Task

Important events are sent to the Logger Task.

Example:

```text
[LOGGER] HIGH PRESSURE
Temperature : 75.0 C
Pressure    : 7.0 Bar
Voltage     : 11.0 V
```

The Logger Task is event-driven. Therefore, no logging event during a monitoring interval is treated as `IDLE`, not as a failure.

## Display Task

Current system status is presented through UART:

```text
============== SYSTEM STATUS ==============
Temperature : 75.0 C
Pressure    : 7.0 Bar
Voltage     : 11.0 V
Machine     : RUNNING
Emergency   : NO
Alarm Bits  : 0x00000002
============================================
```

A dedicated STM32 16x2 LCD driver is planned as a future enhancement.

## Task Health Monitoring

Periodic tasks use heartbeat counters:

```c
volatile uint32_t SensorHeartbeat;
volatile uint32_t ProcessingHeartbeat;
volatile uint32_t DisplayHeartbeat;
```

They increment the counter after successful work:

```c
SensorHeartbeat++;
ProcessingHeartbeat++;
DisplayHeartbeat++;
```

Event-driven tasks use activity counters:

```c
volatile uint32_t LoggerActivity;
volatile uint32_t AlarmActivity;
```

The Monitor Task compares current and previous values.

Example:

```text
[Monitor] Checking system health...
[Monitor] Sensor Task       : OK
[Monitor] Processing Task   : OK
[Monitor] Display Task      : OK
[Monitor] Logger Task       : IDLE
[Monitor] Alarm Task        : IDLE
[Monitor] SYSTEM STATUS     : HEALTHY
```

`IDLE`/`STANDBY` for event-driven tasks is normal when no event is pending.

## FreeRTOS Concepts Demonstrated

- Task creation and management
- Task priorities
- Task states
- Periodic tasks
- `vTaskDelay()`
- Queues
- Binary semaphores
- Mutexes
- Software timers
- Task notifications
- ISR-to-task communication
- Heap management
- UART integration
- Multi-task architecture
- Fault detection
- Recovery detection
- Heartbeat counters
- Event-driven task monitoring

## Hardware and Software

### Hardware

- STM32 Nucleo-F446RE
- ARM Cortex-M4F
- UART for debug/status output

### Software

- FreeRTOS
- Embedded C / C17
- VS Code
- ARM GNU Toolchain
- GNU Make
- STM32 startup/linker configuration

## Build Configuration

Target:

```text
STM32F446RE
ARM Cortex-M4F
```

Compiler:

```text
arm-none-eabi-gcc
```

Representative compiler flags:

```text
-mcpu=cortex-m4
-mthumb
-mfpu=fpv4-sp-d16
-mfloat-abi=hard
-std=c17
-Wall
-Wextra
-Wpedantic
-ffunction-sections
-fdata-sections
-MMD
-MP
-g3
-O0
```

Linker script:

```text
STM32F446RETX_FLASH.ld
```

Build outputs:

```text
build/stm32f446_freertos.elf
build/stm32f446_freertos.hex
build/stm32f446_freertos.bin
```

## Project Structure

```text
Industrial_Monitoring_System/
|
+-- App/
|   +-- Inc/
|   |   +-- app_tasks.h
|   |   +-- sensor_task.h
|   |   +-- processing_task.h
|   |   +-- alarm_task.h
|   |   +-- logger_task.h
|   |   +-- display_task.h
|   |   +-- monitor_task.h
|   |   +-- display_data.h
|   |   +-- logger_event.h
|   |   +-- uart.h
|   |   +-- led.h
|   |
|   +-- Src/
|       +-- main.c
|       +-- app_tasks.c
|       +-- sensor_task.c
|       +-- processing_task.c
|       +-- alarm_task.c
|       +-- logger_task.c
|       +-- display_task.c
|       +-- monitor_task.c
|       +-- uart.c
|       +-- led.c
|       +-- syscalls.c
|
+-- Drivers/
|   +-- Inc/
|   |   +-- stm32f446xx.h 
|   |   +-- stm32f446xx_gpio_driver.h
|   |   +-- stm32f446xx_usart_driver.h
|   |   +-- ring_buffer.h
|   |   +-- stm32f446xx_rcc_driver.h
|   |
|   +-- Src/
|      +-- stm32f446xx_gpio_driver.c
|      +-- stm32f446xx_usart_driver.c
|      +-- ring_buffer.c
|      +-- stm32f446xx_rcc_driver.c

+-- FreeRTOS/
|   +-- include/
|   +-- portable/
|
+-- build/
+-- STM32F446RETX_FLASH.ld
+-- Makefile
+-- README.md
```

Adjust the exact directory names to match the repository.

## Example Runtime Scenarios

### Normal operation

```text
Temperature : 65.0 C
Pressure    : 6.0 Bar
Voltage     : 11.4 V
Alarm Bits  : 0x00000000

[Monitor] SYSTEM STATUS     : HEALTHY
```

### High pressure

```text
Temperature : 75.0 C
Pressure    : 7.0 Bar
Voltage     : 11.0 V

alarmBits = 0x00000002

ALARM: High Pressure
```

Logger output:

```text
[LOGGER] HIGH PRESSURE
Temperature : 75.0 C
Pressure    : 7.0 Bar
Voltage     : 11.0 V
```

### Recovery

```text
Temperature : 80.0 C
Pressure    : 4.0 Bar
Voltage     : 10.8 V

[SYSTEM RECOVERED]
All parameters are within limits
```

## Error Handling

Important RTOS and queue operations are checked for failure.

```c
if (xQueueSend(SensorQueue, &sensorData, pdMS_TO_TICKS(100)) == pdPASS)
{
    SensorHeartbeat++;
}
else
{
    APP_UART_Print("[Sensor] ERROR: Failed to send sensor data\r\n");
}
```

Task creation errors are also reported:

```c
if (status != pdPASS)
{
    APP_UART_Print("[ERROR] Processing Task creation failed\r\n");
}
```

## Memory Usage

The latest successful build has approximately:

```text
RAM   : 27 KB / 128 KB
FLASH : 37 KB / 512 KB
```

Actual values can change as features are added. Use the latest build output for release documentation.

## Future Enhancements

1. FreeRTOS Event Groups
2. Static allocation
3. Stack overflow detection
4. Runtime statistics and CPU utilization
5. Priority inversion demonstration
6. Software watchdog
7. Timestamped logging
8. Logger queue overflow detection
9. STM32 16x2 LCD driver
10. UART command-line interface
11. Persistent event/fault storage
12. Fault injection testing
13. System recovery/reset mechanism
14. More realistic sensor drivers

## This project can demonstrate:

- Why a queue is used between Sensor and Processing Tasks
- Why task notifications are suitable for alarm events
- Queue vs. task notification
- Periodic vs. event-driven tasks
- Mutex vs. semaphore
- RTOS task priorities
- Task blocking and `portMAX_DELAY`
- Heartbeat-based task monitoring
- Fault detection and recovery
- Inter-task communication
- FreeRTOS memory management
- Embedded UART logging
- RTOS error handling

## Status

**Core implementation: Completed**

Current functionality includes:

- Sensor data generation
- Processing and threshold detection
- Alarm notification
- Recovery notification
- Event logging
- System status display
- Task health monitoring
- Heartbeat/activity monitoring

---

# Author

**Sunil Sutar**

Embedded Software Developer

---

# Copyright

© 2026 Sunil Sutar. All Rights Reserved.

This repository is intended for educational, learning, and portfolio purposes.

The source code, documentation, and project structure are the intellectual property of the author. Unauthorized copying, redistribution, or commercial use of this project or any part of it without prior written permission is prohibited.