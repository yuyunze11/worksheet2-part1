#ifndef FB_H
#define FB_H


//#include <stdint.h>

#define FB_BLACK	0x0
#define FB_BLUE		0x1
#define FB_GREEN	0x2
#define FB_CYAN		0x3
#define FB_RED		0x4
#define FB_MAGENTA	0x5
#define FB_BROWN	0x6
#define FB_LIGHT_GREY	0x7
#define FB_DARK_GREY	0x8
#define FB_LIGHT_BLUE	0x9
#define FB_LIGHT_GREEN  0xA
#define FB_LIGHT_CYAN	0xB
#define FB_LIGHT_RED	0xC
#define FB_LIGHT_MAGENTA 0xD
#define FB_LIGHT_BROWN	0xE
#define FB_WHITE	0xF

#define FB_ADDR ((uint16_t*)0xB8000)
#define FB_COLS                 80 
#define FB_ROWS                 25 
#define FB_CMD_PORT             0x3D4 
#define FB_DATA_PORT            0x3D5 
#define FB_HIGH_BYTE_CMD        14 
#define FB_LOW_BYTE_CMD         15 

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;

extern uint8_t fb_fg;
extern uint8_t fb_bg;

void fb_init();

void fb_move_cursor_xy(uint16_t x, uint16_t y);

void fb_print_char(char c);

void fb_print_string(const char* str);

void fb_print_num(int32_t num);

void fb_set_color(uint8_t fg, uint8_t bg);

void fb_clear();


#endif 
