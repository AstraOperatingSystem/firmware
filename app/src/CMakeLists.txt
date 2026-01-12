add_subdirectory(tasks)

target_sources(astra-os-fw PRIVATE
	main.c
)
target_include_directories(astra-os-fw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
