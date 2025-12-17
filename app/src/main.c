#include <stdio.h>
#include <stdint.h>

#include <kpi/kpi.h>

#include "display/display.h"

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "i2c.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"


void keypad_handler(kpi_event_t ev)
{
	char buf[128];
	int len = sprintf(buf, "%d %d\n", ev.button, ev.type);
	HAL_UART_Transmit(&huart1, buf, len, 9999);

	if (ev.type == KPI_EV_SHORT)
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void my_main()
{
	display_t *display = display_init(&hi2c3, 0x27 << 1);

	display_write_str_at(display, "I am worth 20 chars!", 0, 0);
	display_write_str_at(display, "Worth 40 chars I am!", 1, 0);
	display_write_str_at(display, "60 chars am I worth?", 2, 0);
	display_write_str_at(display, "I am worth 80 chars!", 3, 0);

	kpi_bank_t bank;
	kpi_bank_init_static(&bank, keypad_handler, 2, 400, 200);

	while (1)
	{
		HAL_Delay(1);

		uint32_t btn_mask = 0;

		btn_mask |= (1 - HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin)) << 0;
		btn_mask |= (1 - HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin)) << 1;

		kpi_tick(&bank, btn_mask);
	}
}
