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
	if (ev.type == KPI_EV_DOUBLE)
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void my_main()
{
	//display_t *display = display_init(&hi2c3, 0x27);

	kpi_bank_t bank;
	kpi_bank_init_static(&bank, keypad_handler, 2, 500, 500);

	while (1)
	{
		HAL_Delay(1);

		uint32_t btn_mask = 0;

		btn_mask |= HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin) << 0;
		btn_mask |= HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) << 1;

		kpi_tick(&bank, btn_mask);
	}
}
