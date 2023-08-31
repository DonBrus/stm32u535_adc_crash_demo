# ST HAL root directories
INC_ST_HAL_DRIVERS := STM32CubeU5/Drivers/STM32U5xx_HAL_Driver
INC_ST_CMSIS := STM32CubeU5/Drivers/CMSIS

sthal_include_dirs := -I"$(INC_ST_HAL_DRIVERS)/Inc" \
-I"$(INC_ST_CMSIS)/Include" \
-I"$(INC_ST_CMSIS)/Device/ST/STM32U5xx/Include" \
-I"$(INC_ST_CMSIS)/Core/Include"

# Project includes
project_include_dirs := -I"src"

# Whole include directory tree
include_dirs := \
$(sthal_include_dirs) \
$(project_include_dirs)