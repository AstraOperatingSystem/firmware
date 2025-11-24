cmake_minimum_required(VERSION 3.22)

# ===========================
# === Configs and Options ===
# ===========================

# Project name for CMake
set(FW_PROJECT_NAME astra-os-fw)

# Configurations related to 'share'
set(FW_SHARED_DEPEND_TARGETS "" CACHE STRING "What targets in shared to depend on" FORCE)
set(FW_SHARED_LINK_TARGETS "" CACHE STRING "What targets in shared to link" FORCE)

# Development environment options
option(USE_ST_FLASH "Whether to include flashing commands in the toolchain" ON)

# =======================================
# === Project building (do not touch) ===
# =======================================
include(FetchContent)

project(${FW_PROJECT_NAME}
	VERSION 0.1.0
	LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)
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

# Add search paths
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/conan")

# Find needed packages
find_package(kpi REQUIRED)

# Recurse subdirectories
add_subdirectory(cubemx)
add_subdirectory(src)

# Add libraries
target_link_libraries(${EXECUTABLE} PRIVATE cubemx)
target_link_libraries(${EXECUTABLE} PRIVATE kpi::kpi)

# === Flashing and related code ===
if(USE_ST_FLASH)
	find_program(ST_FLASH st-flash)

	add_custom_command(
		OUTPUT  ${PROJECT_BINARY_DIR}/flash_image.bin
		DEPENDS ${EXECUTABLE}
		COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_BINARY_DIR}/flash_image.bin
	)

	add_custom_target(flash_stm
		DEPENDS ${PROJECT_BINARY_DIR}/flash_image.bin
		COMMAND ${ST_FLASH} --reset write ${PROJECT_BINARY_DIR}/flash_image.bin 0x08000000
	)
endif()
