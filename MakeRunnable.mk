######################################
# target
######################################
TARGET:=emWin_eli9325_stm32f103

######################################
# building variables
######################################

# Debug build?
DEBUG:= 1

# Optimization
OPT:=

#######################################
# Paths
#######################################

# Source path
SOURCES_DIR:=  \
src \
src_stm32 \
drivers \


# Firmware library path
PERIFLIB_PATH:=

######################################
# Source
######################################

# C sources

C_SOURCES:= \
src/helloWorld.c \
src_stm32/main.c \
src_stm32/stm32f1xx_it.c \
src_stm32/stm32f1xx_hal_msp.c \
src_stm32/system_stm32f1xx.c \
src_stm32/gpio.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c

# ASM sources
ASM_SOURCES =  \
startup_stm32f103xb.s

######################################
# Firmware library
######################################
PERIFLIB_SOURCES =

#######################################
# Binaries
#######################################

BINPATH =
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################

# Cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

#######################################
# Macros for gcc
#######################################

# AS defines
AS_DEFS =

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F103xB

# Version of compiler
C_COMPILER_VERSION = -std=c99

# AS includes
AS_INCLUDES =

# C includes
C_INCLUDES =  \
-Isrc \
-Isrc_stm32 \
-Idrivers/STM32F1xx_HAL_Driver/Inc \
-Idrivers/STM32F1xx_HAL_Driver/Inc/Legacy \
-Idrivers/CMSIS/Device/ST/STM32F1xx/Include \
-Idrivers/CMSIS/Include

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall $(C_COMPILER_VERSION) -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################

# link script
LDSCRIPT = STM32F103C8Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) \
-Wl,-Map=build/$(TARGET).map,--cref -Wl,--gc-sections

#######################################
# Build the application
#######################################

all: $(TARGET).elf $(TARGET).hex $(TARGET).bin

# List of objects
OBJECTS=$(addprefix build/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# List of ASM program objects
OBJECTS+=$(addprefix build/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)\	))

build/%.o: %.c
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=build/$(notdir $(<:.c=.lst)) $< -o $@

build/%.o: %.s
	$(AS) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

%.hex: %.elf
	$(HEX) $< $@

%.bin: %.elf
	$(BIN) $< $@

clean:
	@ rm -f build/*.o build/*.d build/*.lst *.bin *.elf *.hex build/*.map
