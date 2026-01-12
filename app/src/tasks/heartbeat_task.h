#ifndef _HEARTBEAT_TASK_H_
#define _HEARTBEAT_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#define HEARTBEAT_TASK_STACK_DEPTH configMINIMAL_STACK_SIZE
#define HEARTBEAT_TASK_PRIORITY (configMAX_PRIORITIES - 1)

extern StackType_t _heartbeat_task_stack[HEARTBEAT_TASK_STACK_DEPTH];
extern StaticTask_t _heartbeat_task;

void heartbeat_task_main(void *params);

#endif
