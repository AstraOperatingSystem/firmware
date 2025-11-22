#include <stdint.h>

#include <kpi/kpi.h>

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"

void my_main()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, kpi_bank_destroy(NULL) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_Delay(1000);

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);

	while (1)
	{
		HAL_Delay(100);

		GPIO_PinState state0 = HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin);
		GPIO_PinState state1 = HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, state0 == state1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}
}
