#include "fb.h"
#include "../source/io.h"

//这里用 uint8_t/uint16_t 是因为一般在 fb.h 里已经包含了 <stdint.h>

uint8_t fb_fg = FB_WHITE;   // 默认白字
uint8_t fb_bg = FB_BLACK;   // 默认黑底

//当前光标位置（以字符为单位的 x,y）
static uint16_t fb_cursor_x = 0;
static uint16_t fb_cursor_y = 0;

static volatile uint8_t *fb = (uint8_t *)FB_ADDRESS;

static uint16_t fb_pos(uint16_t x, uint16_t y)
{
    return y * FB_COLS + x;
}

//往第 pos 个格子写一个字符 + 颜色属性
static void fb_write_cell(uint16_t pos, char c, uint8_t fg, uint8_t bg)
{
    fb[pos * 2]     = (uint8_t)c;                // 字符
    fb[pos * 2 + 1] = (bg << 4) | (fg & 0x0F);   // 高4位背景色，低4位前景色
}

//用教材里的 outb 指令更新硬件光标位置
static void fb_update_cursor(void)
{
    uint16_t pos = fb_pos(fb_cursor_x, fb_cursor_y);

    outb(FB_CMD_PORT, FB_HIGH_BYTE_CMD);              // 0x3D4, 14
    outb(FB_DATA_PORT, (pos >> 8) & 0xFF);

    outb(FB_CMD_PORT, FB_LOW_BYTE_CMD);               // 0x3D4, 15
    outb(FB_DATA_PORT, pos & 0xFF);
}

//初始化 framebuffer：颜色/光标归零，然后清屏
void fb_init(void)
{
    fb_fg = FB_WHITE;
    fb_bg = FB_BLACK;
    fb_cursor_x = 0;
    fb_cursor_y = 0;
    fb_clear();
}

//清屏：用当前前景/背景色刷满空格
void fb_clear(void)
{
    uint16_t x, y;

    for (y = 0; y < FB_ROWS; y++) {
        for (x = 0; x < FB_COLS; x++) {
            uint16_t pos = fb_pos(x, y);
            fb_write_cell(pos, ' ', fb_fg, fb_bg);
        }
    }

    fb_cursor_x = 0;
    fb_cursor_y = 0;
    fb_update_cursor();
}
    //设置当前使用的颜色（后面 print 都用它）
void fb_set_color(uint8_t fg, uint8_t bg)
{
    fb_fg = fg;
    fb_bg = bg;
}

//把“逻辑光标”移动到 (x, y)，并更新硬件光标
void fb_move_cursor_xy(uint16_t x, uint16_t y)
{
    if (x >= FB_COLS) x = FB_COLS - 1;
    if (y >= FB_ROWS) y = FB_ROWS - 1;

    fb_cursor_x = x;
    fb_cursor_y = y;
    fb_update_cursor();
}

static void fb_put_char(char c)
{
    if (c == '\n') {
        // 简单处理换行
        fb_cursor_x = 0;
        fb_cursor_y++;
    } else {
        uint16_t pos = fb_pos(fb_cursor_x, fb_cursor_y);
        fb_write_cell(pos, c, fb_fg, fb_bg);
        fb_cursor_x++;

        if (fb_cursor_x >= FB_COLS) {
            fb_cursor_x = 0;
            fb_cursor_y++;
        }
    }

    // 简单起见，暂时不做滚屏，超出就写到下面去了
    if (fb_cursor_y >= FB_ROWS) {
        fb_cursor_y = FB_ROWS - 1;
    }

    fb_update_cursor();
}

//从当前光标位置开始，输出一整串字符串
void fb_print_string(const char *str)
{
    while (*str) {
        fb_put_char(*str);
        str++;
    }
}




















