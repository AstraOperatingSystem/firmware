add_library(cubemx STATIC)
target_compile_definitions(cubemx PRIVATE ${COMPILER_DEFINES})
target_compile_options(${EXECUTABLE} PRIVATE -Os -ffunction-sections -fdata-sections -g -flto)
target_link_options(${EXECUTABLE} PRIVATE -T ${LINKER_SCRIPT} --specs=nano.specs -Wl,--gc-sections -flto)
target_sources(cubemx PRIVATE
	startup_stm32f411xe.s
)
add_subdirectory(Core)
add_subdirectory(Drivers)
