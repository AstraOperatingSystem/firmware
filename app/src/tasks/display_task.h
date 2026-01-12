#ifndef _DISPLAY_TASK_H_
#define _DISPLAY_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

#define DISPLAY_TASK_STACK_DEPTH 512
#define DISPLAY_TASK_PRIORITY 1

extern StackType_t _display_task_stack[DISPLAY_TASK_STACK_DEPTH];
extern StaticTask_t _display_task;

void display_task_main(void *params);

#endif
