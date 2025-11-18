target_include_directories(${EXECUTABLE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${EXECUTABLE} PRIVATE
	cmsis_os2.c
)
