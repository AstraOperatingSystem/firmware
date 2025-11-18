target_sources(${EXECUTABLE} PRIVATE
	croutine.c
	event_groups.c
	list.c
	queue.c
	stream_buffer.c
	tasks.c
	timers.c
)
add_subdirectory(include)
add_subdirectory(CMSIS_RTOS_V2)
add_subdirectory(portable)
