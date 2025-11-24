add_library(cubemx STATIC)
target_compile_definitions(cubemx PRIVATE ${COMPILER_DEFINES})
target_compile_options(cubemx PRIVATE -Os -ffunction-sections -fdata-sections -g -flto)
target_link_options(cubemx PRIVATE -T ${LINKER_SCRIPT} -Wl,--gc-sections -flto)
target_sources(cubemx PRIVATE
	startup_stm32f411xe.s
)
add_subdirectory(Core)
add_subdirectory(Drivers)
