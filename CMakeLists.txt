cmake_minimum_required(VERSION 3.22)

project(astra-os-firmware VERSION 0.1.0 LANGUAGES C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(cubemx)
add_subdirectory(app)
