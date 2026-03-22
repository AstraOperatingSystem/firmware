add_library(cubemx OBJECT)
target_compile_definitions(cubemx PRIVATE ${COMPILER_DEFINES})
target_compile_options(cubemx PRIVATE -Os -ffunction-sections -fdata-sections -g -flto)
target_sources(cubemx PRIVATE
	startup_stm32f412zx.s
)
add_subdirectory(Core)
add_subdirectory(Drivers)
