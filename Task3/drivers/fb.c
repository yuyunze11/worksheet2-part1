#include "fb.h"
#include "../source/io.h"

// 当前前景色 / 背景色（默认：白字黑底）
uint8_t fb_fg = FB_WHITE;
uint8_t fb_bg = FB_BLACK;

// 当前光标位置
static uint16_t fb_cursor_x = 0;
static uint16_t fb_cursor_y = 0;

// 计算 (x, y) 在显存中的下标
static uint16_t fb_pos(uint16_t x, uint16_t y)
{
    return y * FB_COLS + x;
}

// 更新硬件光标
static void fb_update_cursor(void)
{
    uint16_t pos = fb_pos(fb_cursor_x, fb_cursor_y);

    outb(FB_CMD_PORT, FB_HIGH_BYTE_CMD);
    outb(FB_DATA_PORT, (pos >> 8) & 0xFF);
    outb(FB_CMD_PORT, FB_LOW_BYTE_CMD);
    outb(FB_DATA_PORT, pos & 0xFF);
}

// 向上滚动一行
static void fb_scroll(void)
{
    if (fb_cursor_y < FB_ROWS)
        return;

    // 1~24 行搬到 0~23 行
    for (uint16_t y = 1; y < FB_ROWS; y++) {
        for (uint16_t x = 0; x < FB_COLS; x++) {
            FB_ADDR[fb_pos(x, y - 1)] = FB_ADDR[fb_pos(x, y)];
        }
    }

    // 清空最后一行
    uint16_t attr = (fb_bg << 4) | fb_fg;
    uint16_t blank = (attr << 8) | ' ';
    uint16_t last_row = FB_ROWS - 1;

    for (uint16_t x = 0; x < FB_COLS; x++) {
        FB_ADDR[fb_pos(x, last_row)] = blank;
    }

    fb_cursor_y = last_row;
    fb_cursor_x = 0;
    fb_update_cursor();
}

// 初始化帧缓冲
void fb_init(void)
{
    fb_fg = FB_WHITE;
    fb_bg = FB_BLACK;
    fb_cursor_x = 0;
    fb_cursor_y = 0;
    fb_clear();
}

// 移动光标到 (x, y)
void fb_move_cursor_xy(uint16_t x, uint16_t y)
{
    if (x >= FB_COLS) x = FB_COLS - 1;
    if (y >= FB_ROWS) y = FB_ROWS - 1;

    fb_cursor_x = x;
    fb_cursor_y = y;
    fb_update_cursor();
}

// 打印单个字符
void fb_print_char(char c)
{
    if (c == '\n') {
        fb_cursor_x = 0;
        fb_cursor_y++;
    } else if (c == '\r') {
        fb_cursor_x = 0;
    } else {
        if (fb_cursor_y >= FB_ROWS) {
            fb_scroll();
        }

        uint16_t attr = (fb_bg << 4) | fb_fg;
        uint16_t data = (attr << 8) | (uint8_t)c;

        FB_ADDR[fb_pos(fb_cursor_x, fb_cursor_y)] = data;

        fb_cursor_x++;
        if (fb_cursor_x >= FB_COLS) {
            fb_cursor_x = 0;
            fb_cursor_y++;
        }
    }

    if (fb_cursor_y >= FB_ROWS) {
        fb_scroll();
    } else {
        fb_update_cursor();
    }
}

// 打印字符串
void fb_print_string(const char* str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        fb_print_char(str[i]);
    }
}

// 递归打印无符号整数
static void fb_print_num_recursive(uint32_t n)
{
    if (n >= 10) {
        fb_print_num_recursive(n / 10);
    }
    fb_print_char('0' + (n % 10));
}

// 打印有符号整数
void fb_print_num(int32_t num)
{
    if (num < 0) {
        fb_print_char('-');
        fb_print_num_recursive((uint32_t)(-num));
    } else {
        fb_print_num_recursive((uint32_t)num);
    }
}

// 设置前景/背景色
void fb_set_color(uint8_t fg, uint8_t bg)
{
    fb_fg = fg & 0x0F;
    fb_bg = bg & 0x0F;
}

// 清屏
void fb_clear(void)
{
    uint16_t attr = (fb_bg << 4) | fb_fg;
    uint16_t blank = (attr << 8) | ' ';

    for (uint16_t y = 0; y < FB_ROWS; y++) {
        for (uint16_t x = 0; x < FB_COLS; x++) {
            FB_ADDR[fb_pos(x, y)] = blank;
        }
    }

    fb_cursor_x = 0;
    fb_cursor_y = 0;
    fb_update_cursor();
}




















