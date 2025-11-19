target_sources(cubemx PRIVATE
	stream_buffer.c
	queue.c
	tasks.c
	list.c
	event_groups.c
	croutine.c
	timers.c
)
add_subdirectory(CMSIS_RTOS_V2)
add_subdirectory(include)
add_subdirectory(portable)
