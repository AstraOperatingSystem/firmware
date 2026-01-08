cmake_minimum_required(VERSION 4.2.1)

# ===========================
# === Configs and Options ===
# ===========================

# Project name for CMake
set(FW_PROJECT_NAME astra-os-fw)

# =======================================
# === Project building (do not touch) ===
# =======================================
project(${FW_PROJECT_NAME}
	VERSION 0.1.0
	LANGUAGES C ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(EXECUTABLE ${FW_PROJECT_NAME})
add_executable(${EXECUTABLE} "")

# Set compiler/linker options
target_compile_definitions(${EXECUTABLE} PRIVATE ${COMPILER_DEFINES})
target_compile_options(${EXECUTABLE} PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Wconversion
	-O0
	-ffunction-sections
	-fdata-sections
    -g
	-flto
)
target_link_options(${EXECUTABLE} PRIVATE
	-T ${CMAKE_CURRENT_SOURCE_DIR}/STM32F411XX_FLASH.ld
	--specs=nano.specs
	-Wl,--gc-sections
	-flto
)
target_compile_definitions(${EXECUTABLE} PRIVATE
	STM32F411xE
)

# Add CPM (package management)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake)

# Add package dependencies
CPMAddPackage("gh:AstraOperatingSystem/libkpi#master")
CPMAddPackage("gh:AstraOperatingSystem/libuartl#master")

# Add FreeRTOS
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FreeRTOS.cmake)

# Recurse subdirectories
add_subdirectory(src)
add_subdirectory(drivers)

# Add libraries
target_link_libraries(${EXECUTABLE} PRIVATE freertos_kernel)
target_link_libraries(${EXECUTABLE} PRIVATE cubemx)
target_link_libraries(${EXECUTABLE} PRIVATE kpi)
target_link_libraries(${EXECUTABLE} PRIVATE uartl)

# === Flashing and debugging code ===
find_program(OPENOCD openocd)
set(OPENOCD_BOARD "board/st_nucleo_f4.cfg")

add_custom_command(
	OUTPUT  ${PROJECT_BINARY_DIR}/flash_image.bin
	DEPENDS ${EXECUTABLE}
	COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_BINARY_DIR}/flash_image.bin
)

add_custom_target(flash
	DEPENDS ${PROJECT_BINARY_DIR}/flash_image.bin
	COMMAND ${OPENOCD} -f ${OPENOCD_BOARD} -c "program ${PROJECT_BINARY_DIR}/flash_image.bin verify reset exit 0x08000000"
)
