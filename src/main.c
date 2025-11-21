#include <stdint.h>

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"

void my_main()
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart1, "Yo\r\n", 4, 500);

	while (1)
	{
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}
