#include "display/display.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



struct display_t
{
	I2C_HandleTypeDef *handle;
	uint16_t address;
	bool backlight, display, cursor, blink;
};



//Bit mask for display pins
#define PIN_E  0b00000100
#define PIN_RW 0b00000010
#define PIN_RS 0b00000001
#define PIN_BL 0b00001000
#define PIN_D4 0b00010000
#define PIN_D5 0b00100000
#define PIN_D6 0b01000000
#define PIN_D7 0b10000000

//Display commands
#define CMD_CLEAR 0x01
#define CMD_HOME  0x02
#define CMD_ENTRY 0x04
#define CMD_DISP  0x08
#define CMD_CODS  0x10
#define CMD_FUNC  0x20
#define CMD_CGADR 0x40
#define CMD_DRADR 0x80

//Flags for entry mode
#define ENTRY_NORM  0x02
#define ENTRY_SHIFT 0x01

//Flags for display
#define DISP_PWR  0x04
#define DISP_OFF  0x00
#define DISP_CURS 0x02
#define DISP_BLNK 0x01

//Flags for CODS
#define CODS_CURL 0x00
#define CODS_CURR 0x04
#define CODS_SCRL 0x08
#define CODS_SCRR 0x0C

//Flags for function
#define FUNC_4BIT  0x00
#define FUNC_8BIT  0x10
#define FUNC_1LIN  0x00
#define FUNC_2LIN  0x08
#define FUNC_5x8D  0x00
#define FUNC_5x11D 0x04



static void write_cmd(I2C_HandleTypeDef *handle, uint16_t addr, unsigned int cmd, bool backlight)
{
	uint8_t byte;

	byte = (cmd & 0xF0) | (backlight ? PIN_BL : 0) | PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);
	byte &= ~PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);

	byte = ((cmd << 4) & 0xF0) | (backlight ? PIN_BL : 0) | PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);
	byte &= ~PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);
}

static void write_char(I2C_HandleTypeDef *handle, uint16_t addr, char ch, bool backlight)
{
	uint8_t byte;

	byte = (ch & 0xF0) | PIN_RS | (backlight ? PIN_BL : 0) | PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);
	byte &= ~PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);

	byte = ((ch << 4) & 0xF0) | PIN_RS | (backlight ? PIN_BL : 0) | PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);
	byte &= ~PIN_E;
	HAL_I2C_Master_Transmit(handle, addr, &byte, 1, 9999);
}



display_t *display_init(I2C_HandleTypeDef *handle, uint16_t addr)
{
	if (handle == NULL)
	{
		//logger_error("display_init received a NULL I2C handle.\n");
		return NULL;
	}
	if (addr >= 0x80)
	{
		//logger_error("display_init received an invalid address: %d.\n", addr);
		return NULL;
	}

	display_t * ret = malloc(sizeof(display_t));
	if (!ret)
	{
		//logger_error("display_init failed to allocate memory.");
		return NULL;
	}

	ret->backlight = true;
	ret->handle = handle;
	ret->address = addr;

	//Literal magic, idk why it's needed, idk what the values are
	//All I know is it no workey without this
	//Average programming moment
	write_cmd(ret->handle, ret->address, 0x03, false);
	write_cmd(ret->handle, ret->address, 0x03, false);
	write_cmd(ret->handle, ret->address, 0x03, false);
	write_cmd(ret->handle, ret->address, 0x02, false);

	write_cmd(ret->handle, ret->address, CMD_FUNC | FUNC_4BIT | FUNC_2LIN | FUNC_5x8D, ret->backlight);
	write_cmd(ret->handle, ret->address, CMD_DISP | DISP_PWR, ret->backlight);
	write_cmd(ret->handle, ret->address, CMD_CLEAR, ret->backlight);
	write_cmd(ret->handle, ret->address, CMD_ENTRY | ENTRY_NORM, ret->backlight);
	HAL_Delay(200); //REVIEW: Why??

	return ret;
}

void display_destroy(display_t *display)
{
	if (!display)
	{
		//logger_error("display_destroy received a NULL display.");
		return;
	}

	free(display);
}



void display_clear(display_t *display)
{
	if (!display)
	{
		//logger_error("display_clear received a NULL display.");
		return;
	}

	write_cmd(display->handle, display->address, CMD_CLEAR, display->backlight);
}

void display_set_backlight(display_t *display, bool backlight)
{
	if (!display)
	{
		//logger_error("display_set_backlight received a NULL display.");
		return;
	}

	display->backlight = backlight;
	uint8_t byte = backlight ? PIN_BL : 0;
	HAL_I2C_Master_Transmit(display->handle, display->address, &byte, 1, 9999);
}

void display_set_cursor(display_t *display, int lin, int col)
{
	if (!display)
	{
		//logger_error("display_set_cursor received a NULL display.");
		return;
	}

	int pos = col % 20;
	switch (lin % 4)
	{
		case 1:
			pos += 0x40;
			break;

		case 2:
			pos += 0x14;
			break;

		case 3:
			pos += 0x54;
			break;

		case 0:
		default:
			break;
	}

	write_cmd(display->handle, display->address, CMD_DRADR | (pos & 0x7F), display->backlight);
}

void display_write_ch(display_t *display, char ch)
{
	if (!display)
	{
		//logger_error("display_write_ch received a NULL display.");
		return;
	}

	write_char(display->handle, display->address, ch, display->backlight);
}

void display_write_str(display_t *display, char *str)
{
	if (!display)
	{
		//logger_error("display_write_str received a NULL display.");
		return;
	}
	if (!str)
	{
		//logger_error("display_write_str received a NULL str.");
		return;
	}

	for (int i = 0; str[i]; ++i)
		write_char(display->handle, display->address, str[i], display->backlight);
}

void display_write_str_at(display_t *display, char *str, int lin, int col)
{
	if (!display)
	{
		//logger_error("display_write_str_at received a NULL display.");
		return;
	}
	if (!str)
	{
		//logger_error("display_write_str_at received a NULL str.");
		return;
	}

	display_set_cursor(display, lin, col);
	display_write_str(display, str);
}

void display_set_display_on(display_t *display, bool on)
{
	if (!display)
	{
		//logger_error("display_set_display_on received a NULL display.");
		return;
	}

	display->display = on;
	char cmd = CMD_DISP | (display->display ? 0x4 : 0x0) | (display->cursor ? 0x2 : 0x0) | (display->blink ? 0x1 : 0x0);
	write_cmd(display->handle, display->address, cmd, display->backlight);
}

void display_set_cursor_show(display_t *display, bool show)
{
	if (!display)
	{
		//logger_error("display_set_cursor_show received a NULL display.");
		return;
	}

	display->cursor = show;
	char cmd = CMD_DISP | (display->display ? 0x4 : 0x0) | (display->cursor ? 0x2 : 0x0) | (display->blink ? 0x1 : 0x0);
	write_cmd(display->handle, display->address, cmd, display->backlight);
}

void display_set_cursor_blink(display_t *display, bool blink)
{
	if (!display)
	{
		//logger_error("display_set_cursor_blink received a NULL display.");
		return;
	}

	display->blink = blink;
	char cmd = CMD_DISP | (display->display ? 0x4 : 0x0) | (display->cursor ? 0x2 : 0x0) | (display->blink ? 0x1 : 0x0);
	write_cmd(display->handle, display->address, cmd, display->backlight);
}

void display_set_custom_char(display_t *display, uint8_t char_idx, uint64_t data)
{
	if (!display)
	{
		//logger_error("display_set_custom_char received a NULL display.");
		return;
	}
	if (char_idx >= 8)
	{
		//logger_error("display_set_custom_char was given an invalid char_idx: %d.\n", char_idx);
		return;
	}

	write_cmd(display->handle, display->address, CMD_CGADR | (char_idx << 3), display->backlight);

	for (int i = 7; i >= 0; i--)
		write_char(display->handle, display->address, (data >> (i * 8)) & 0xFF, display->backlight);
}
