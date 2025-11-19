target_sources(cubemx PRIVATE
	stm32f4xx_it.c
	stm32f4xx_hal_msp.c
	stm32f4xx_hal_timebase_tim.c
	main.c
	system_stm32f4xx.c
	sysmem.c
	syscalls.c
	gpio.c
	i2c.c
	usart.c
)
