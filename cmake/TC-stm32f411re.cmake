set(CMAKE_SYSTEM_NAME        Generic)
set(CMAKE_SYSTEM_PROCESSOR   arm)

# Toolchain
set(TOOLCHAIN_PREFIX         arm-none-eabi-)
set(CMAKE_C_COMPILER         ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER       ${CMAKE_C_COMPILER})
set(CMAKE_OBJCOPY            ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP            ${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE               ${TOOLCHAIN_PREFIX}size)
set(CMAKE_LINKER             ${TOOLCHAIN_PREFIX}ld)

# Skip link check in toolchain validation
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Find configuration (standard)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Base compiler defines
set(COMPILER_DEFINES ${COMPILER_DEFINES}
	USE_FULL_LL_DRIVER
	USE_HAL_DRIVER
)

# Set MCU flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard ")

# CPU architecture for gcc
set(CMAKE_C_FLAGS_INIT "-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Set FreeRTOS options
set(FREERTOS_PORT "GCC_ARM_CM4" CACHE STRING "" FORCE)

# Specify linker script
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/cubemx/STM32F411XX_FLASH.ld)

# Set CPU for later conditional compilation
set(COMPILER_DEFINES ${COMPILER_DEFINES}
	STM32F411xE
)

# Set compiler args
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")

# Set linker args
set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS} ${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
