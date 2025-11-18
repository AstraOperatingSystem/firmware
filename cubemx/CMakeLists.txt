target_sources(${EXECUTABLE} PRIVATE
	startup_stm32f411xe.s
)
add_subdirectory(Core)
add_subdirectory(Drivers)
add_subdirectory(Middlewares)
