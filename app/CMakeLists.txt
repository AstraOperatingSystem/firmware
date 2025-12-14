cmake_minimum_required(VERSION 3.22)

# ===========================
# === Configs and Options ===
# ===========================

# Project name for CMake
set(FW_PROJECT_NAME astra-os-fw)

# Configurations related to 'share'
set(FW_SHARED_DEPEND_TARGETS "" CACHE STRING "What targets in shared to depend on" FORCE)
set(FW_SHARED_LINK_TARGETS "" CACHE STRING "What targets in shared to link" FORCE)

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
	-O0
	-ffunction-sections
	-fdata-sections
    -g
	-flto
)
target_link_options(${EXECUTABLE} PRIVATE
	-T ${PROJECT_SOURCE_DIR}/${LINKER_SCRIPT}
	--specs=nano.specs
	-Wl,--gc-sections
	-flto
)
target_compile_definitions(${EXECUTABLE} PRIVATE
	STM32F411xE
)

# Add search paths
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

# Find needed packages
find_package(kpi REQUIRED)

# Recurse subdirectories
add_subdirectory(src)
add_subdirectory(drivers)

# Add libraries
target_link_libraries(${EXECUTABLE} PRIVATE cubemx)
target_link_libraries(${EXECUTABLE} PRIVATE kpi::kpi)

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
