//display.h - Raw control over I2C display hardware

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"



#define DISP_LINES 4
#define DISP_COLS 20
#define DISP_SIZE (DISP_COLS * DISP_LINES)

#define DISP_I2C0 0
#define DISP_I2C1 1

#define DISP_CHAR_ARROWR '\x7e'
#define DISP_CHAR_ARROWL '\x7f'
#define DISP_CHAR_DOT_HIGH '\xa5'
#define DISP_CHAR_BOX '\xdb'
#define DISP_CHAR_DEGREE '\xdf'
#define DISP_CHAR_ALPHA '\xe0'
#define DISP_CHAR_BETA '\xe2'
#define DISP_CHAR_EPSILON '\xe3'
#define DISP_CHAR_MU '\xe4'
#define DISP_CHAR_SQRT '\xe9'
#define DISP_CHAR_OMEGA '\xf4'
#define DISP_CHAR_SUM '\xf7'
#define DISP_CHAR_PI '\xf8'
#define DISP_CHAR_DOT_DIV '\xfd'
#define DISP_CHAR_BLACK '\xff'

#define DISP_CHAR_NOTE '\x01'
#define DISP_CHAR_LIST '\x02'
#define DISP_CHAR_SEARCH '\x03'
#define DISP_CHAR_WIFI '\x04'
#define DISP_CHAR_BLUETOOTH '\x05'
#define DISP_CHAR_TERMO '\x06'
#define DISP_CHAR_SHIFTER '\x07'

typedef struct display_t display_t;

display_t *display_init(I2C_HandleTypeDef *handle, uint16_t addr);
void display_destroy(display_t *display);

void display_set_backlight(display_t *display, bool backlight);
void display_set_cursor(display_t *display, int lin, int col);
void display_clear(display_t *display);
void display_write_ch(display_t *display, char ch);
void display_write_str(display_t *display, char *str);
void display_write_str_at(display_t *display, char *str, int lin, int col);

void display_set_display_on(display_t *display, bool on);
void display_set_cursor_show(display_t *display, bool show);
void display_set_cursor_blink(display_t *display, bool blink);
void display_set_custom_char(display_t *display, uint8_t char_idx, uint64_t data);

#endif
