#include "display_task.h"

#include "display/display.h"
#include "i2c.h"

#include "display_chars.h"



StackType_t _display_task_stack[DISPLAY_TASK_STACK_DEPTH];
StaticTask_t _display_task;



static void program_chars(display_t *display);
static void draw_banner(display_t *display);



void display_task_main(void *params)
{
	(void)params;

	display_t *display = display_init(&hi2c3, 0x27 << 1);
	vTaskDelay(5);

	program_chars(display);
	draw_banner(display);

	while (1)
	{
		vTaskDelay(20);
	}

	vTaskDelete(NULL);
}



static void program_chars(display_t *display)
{
	//Bottom T
	//L1-.....
	//L2-.....
	//L3-.....
	//L4-#####
	//L5-..#..
	//L6-..#..
	//L7-.....
	//L8-XXXXX
	//                         L1-.....L2-.....L3-.....L4-#####L5-..#..L6-..#..L7-.....L8-XXXXX
	uint64_t char_t_bottom = 0b0000000000000000000000000001111100000100000001000000000000000000;

	//Right T
	//L1-.....
	//L2-..#..
	//L3-..#..
	//L4-..###
	//L5-..#..
	//L6-..#..
	//L7-.....
	//L8-XXXXX
	//                        L1-.....L2-..#..L3-..#..L4-..###L5-..#..L6-..#..L7-.....L8-XXXXX
	uint64_t char_t_right = 0b0000000000000100000001000000011100000100000001000000000000000000;

	//BR Corner
	//L1-.....
	//L2-.....
	//L3-.....
	//L4-..###
	//L5-..#..
	//L6-..#..
	//L7-.....
	//L8-XXXXX
	//                          L1-.....L2-.....L3-.....L4-..###L5-..#..L6-..#..L7-.....L8-XXXXX
	uint64_t char_br_corner = 0b0000000000000000000000000000011100000100000001000000000000000000;

	//Back Slash
	//L1-.....
	//L2-#....
	//L3-.#...
	//L4-..#..
	//L5-...#.
	//L6-....#
	//L7-.....
	//L8-XXXXX
	//                       L1-.....L2-#....L3-.#...L4-..#..L5-...#.L6-....#L7-.....L8-XXXXX
	uint64_t char_bslash = 0b0000000000010000000010000000010000000010000000010000000000000000;

	//Low Slash
	//L1-.....
	//L2-.....
	//L3-.....
	//L4-....#
	//L5-...#.
	//L6-..#..
	//L7-.....
	//L8-XXXXX
	//                          L1-.....L2-.....L3-.....L4-....#L5-...#.L6-..#..L7-.....L8-XXXXX
	uint64_t char_low_slash = 0b0000000000000000000000000000000100000010000001000000000000000000;


	display_set_custom_char(display, CHAR_BOTTOM_T, char_t_bottom);
	display_set_custom_char(display, CHAR_RIGHT_T, char_t_right);
	display_set_custom_char(display, CHAR_BR_CORNER, char_br_corner);
	display_set_custom_char(display, CHAR_BSLASH, char_bslash);
	display_set_custom_char(display, CHAR_LOW_SLASH, char_low_slash);
}

static void draw_banner(display_t *display)
{
	//  /-\ / -T- r-\ /-\     nc
	//  |_| \  |  p-+ |_|     nc
	//  | | /  |  | \ | |     nc

	display_clear(display);

	display_set_cursor(display, 0, 1);
	display_write_ch(display, CHAR_LOW_SLASH);
	display_write_ch(display, '-');
	display_write_ch(display, CHAR_LOW_BSLASH);
	display_write_str(display, " / -");
	display_write_ch(display, CHAR_BOTTOM_T);
	display_write_str(display, "- ");
	display_write_ch(display, CHAR_BR_CORNER);
	display_write_ch(display, '-');
	display_write_ch(display, CHAR_LOW_BSLASH);
	display_write_ch(display, ' ');
	display_write_ch(display, CHAR_LOW_SLASH);
	display_write_ch(display, '-');
	display_write_ch(display, CHAR_LOW_BSLASH);

	display_set_cursor(display, 1, 1);
	display_write_str(display, "|-| ");
	display_write_ch(display, CHAR_BSLASH);
	display_write_str(display, "  |  ");
	display_write_ch(display, CHAR_RIGHT_T);
	display_write_str(display, "-+ |_|");

	display_set_cursor(display, 2, 1);
	display_write_str(display, "| | /  |  | |");
	display_write_str(display, " | |");
}
