target_include_directories(cubemx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(cubemx PRIVATE
	cmsis_os2.c
)
