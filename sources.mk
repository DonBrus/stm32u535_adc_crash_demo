########################## ST HAL SOURCES ##########################
# ST HAL root directories
SRC_ST_HAL_DIR := STM32CubeU5
SRC_ST_HAL_DRIVERS := $(SRC_ST_HAL_DIR)/Drivers/STM32U5xx_HAL_Driver
SRC_ST_CMSIS := $(SRC_ST_HAL_DIR)/Drivers/CMSIS

st_hal_sources := \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_adc.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_adc_ex.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_cortex.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_dma.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_exti.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_flash.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_gpio.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_icache.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_pwr.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_pwr_ex.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_rcc.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_rcc_ex.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_tim.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_hal_tim_ex.c \

st_ll_sources := \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_dma.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_exti.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_gpio.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_icache.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_pwr.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_rcc.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_tim.c \
$(SRC_ST_HAL_DRIVERS)/Src/stm32u5xx_ll_crc.c \


SRC_DIR:= src
project_sources := \
$(SRC_DIR)/adc.c \
$(SRC_DIR)/interrupts.c \
$(SRC_DIR)/main.c \
$(SRC_DIR)/msp.c \
$(SRC_DIR)/startup.s \
$(SRC_DIR)/sysmem.c \
$(SRC_DIR)/syscalls.c \
$(SRC_DIR)/system_init.c\
$(SRC_DIR)/timebase_init.c


sources := \
$(st_hal_sources) \
$(st_ll_sources) \
$(project_sources)
