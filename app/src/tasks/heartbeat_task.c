#include "heartbeat_task.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "gpio.h"



StackType_t _heartbeat_task_stack[HEARTBEAT_TASK_STACK_DEPTH];
StaticTask_t _heartbeat_task;



void heartbeat_task_main(void *params)
{
	(void)params;

	TickType_t last_wake = xTaskGetTickCount();

	while (1)
	{
		xTaskDelayUntil(&last_wake, 298);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		xTaskDelayUntil(&last_wake, 2);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	}
}
