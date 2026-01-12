#include "display_task.h"

#include "display/display.h"
#include "i2c.h"


StackType_t _display_task_stack[DISPLAY_TASK_STACK_DEPTH];
StaticTask_t _display_task;
void display_task_main(void *params)
{
	(void)params;

	display_t *display = display_init(&hi2c3, 0x27 << 1);

	display_write_str_at(display, "I am worth 20 chars!", 0, 0);
	display_write_str_at(display, "Worth 40 chars I am!", 1, 0);
	display_write_str_at(display, "60 chars am I worth?", 2, 0);
	display_write_str_at(display, "Damn worth 80 chars!", 3, 0);

	while (1)
	{
		
	}

	vTaskDelete(NULL);
}
