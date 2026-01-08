# Add FetchContent
include(FetchContent)

# Add FreeRTOS
FetchContent_Declare(freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        V11.2.0
)

add_library(freertos_config INTERFACE)

target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})

target_include_directories(freertos_config SYSTEM
INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)

# Set FreeRTOS port
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)

FetchContent_MakeAvailable(freertos_kernel)

target_compile_options(freertos_kernel PRIVATE -g)
target_compile_options(freertos_kernel_port PRIVATE -g)


