#==============================================================================
# File:        Makefile
# Author:      Sunil Sutar
# Description: Build configuration for the STM32F446RE FreeRTOS
#              Industrial Monitoring System.
#
# Target:
#     STM32F446RE - ARM Cortex-M4F
#
# Toolchain:
#     arm-none-eabi-gcc
#
# Build system:
#     GNU Make
#
# Output:
#     ELF / HEX / BIN
#
# RTOS:
#     FreeRTOS
#============================================================================== 

################################################################################
# Project
################################################################################

TARGET = stm32f446_freertos

################################################################################
# Toolchain
################################################################################

PREFIX  = arm-none-eabi-

CC      = $(PREFIX)gcc
AS      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
SIZE    = $(PREFIX)size

################################################################################
# Directories
################################################################################

BUILD_DIR = build

################################################################################
# Source Files
################################################################################

# Application
C_SOURCES := $(wildcard App/Src/*.c)

# Drivers
C_SOURCES += $(wildcard Drivers/Src/*.c)

# FreeRTOS Kernel
C_SOURCES += $(wildcard FreeRTOS/*.c)

# FreeRTOS ARM Port
C_SOURCES += $(wildcard FreeRTOS/portable/GCC/ARM_CM4F/*.c)

# FreeRTOS Heap
C_SOURCES += FreeRTOS/portable/MemMang/heap_4.c

# Startup
ASM_SOURCES := $(wildcard Startup/*.s)

################################################################################
# Include Paths
################################################################################

C_INCLUDES = \
-IApp/Inc \
-IDrivers/Inc \
-IFreeRTOS/ \
-IFreeRTOS/include \
-IFreeRTOS/portable/GCC/ARM_CM4F

################################################################################
# MCU
################################################################################

MCU = cortex-m4

################################################################################
# Compiler Flags
################################################################################

CFLAGS =

CFLAGS += -mcpu=$(MCU)
CFLAGS += -mthumb
CFLAGS += -mfpu=fpv4-sp-d16
CFLAGS += -mfloat-abi=hard

CFLAGS += -std=c17

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpedantic

CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections

CFLAGS += -MMD
CFLAGS += -MP

CFLAGS += -g3
CFLAGS += -O0

################################################################################
# Assembler Flags
################################################################################

ASFLAGS =

ASFLAGS += -mcpu=$(MCU)
ASFLAGS += -mthumb
ASFLAGS += -mfpu=fpv4-sp-d16
ASFLAGS += -mfloat-abi=hard
ASFLAGS += -x assembler-with-cpp

################################################################################
# Linker Script
################################################################################

LDSCRIPT = STM32F446RETX_FLASH.ld

################################################################################
# Linker Flags
################################################################################

LDFLAGS =

LDFLAGS += -mcpu=$(MCU)
LDFLAGS += -mthumb
LDFLAGS += -mfpu=fpv4-sp-d16
LDFLAGS += -mfloat-abi=hard
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS += -specs=nano.specs
LDFLAGS += -u _printf_float
LDFLAGS += -Wl,--print-memory-usage

################################################################################
# Object Files
################################################################################

OBJECTS = \
$(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o))) \
$(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))

DEPS = $(OBJECTS:.o=.d)

################################################################################
# Build Rules
################################################################################

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

################################################################################
# Compile Application
################################################################################

$(BUILD_DIR)/%.o: App/Src/%.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

################################################################################
# Compile Drivers
################################################################################

$(BUILD_DIR)/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

################################################################################
# Compile FreeRTOS Kernel
################################################################################

$(BUILD_DIR)/%.o: FreeRTOS/%.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

################################################################################
# Compile FreeRTOS ARM Port
################################################################################

$(BUILD_DIR)/%.o: FreeRTOS/portable/GCC/ARM_CM4F/%.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

################################################################################
# Compile Heap
################################################################################

$(BUILD_DIR)/%.o: FreeRTOS/portable/MemMang/%.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

################################################################################
# Assemble
################################################################################

$(BUILD_DIR)/%.o: Startup/%.s
	$(AS) $(ASFLAGS) $(C_INCLUDES) -c $< -o $@

################################################################################
# Link
################################################################################

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@
	$(OBJCOPY) -O ihex   $@ $(BUILD_DIR)/$(TARGET).hex
	$(OBJCOPY) -O binary $@ $(BUILD_DIR)/$(TARGET).bin

################################################################################
# Clean
################################################################################

clean:
	rm -rf $(BUILD_DIR)

################################################################################
# Flash (STM32CubeProgrammer CLI)
################################################################################

flash:
	STM32_Programmer_CLI -c port=SWD -w $(BUILD_DIR)/$(TARGET).hex -v -rst

################################################################################
# OpenOCD Flash
################################################################################

flash-openocd:
	openocd \
	-f interface/stlink.cfg \
	-f target/stm32f4x.cfg \
	-c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

################################################################################
# Debug
################################################################################

debug:
	arm-none-eabi-gdb $(BUILD_DIR)/$(TARGET).elf

.PHONY: all clean flash flash-openocd debug