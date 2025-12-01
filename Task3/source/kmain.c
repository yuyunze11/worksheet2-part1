#include "../drivers/fb.h"

void kmain(void) 
{
    fb_init();      // 初始化帧缓冲
    fb_clear();     // 清屏

    // 第 0 行：基础输出（白字黑底）
    fb_set_color(FB_WHITE, FB_BLACK);
    fb_move_cursor_xy(0, 0);
    fb_print_string("Task3 framebuffer test");

    // 第 1 行：一个蓝色示例（白字蓝底）
    fb_set_color(FB_WHITE, FB_BLUE);
    fb_move_cursor_xy(0, 1);
    fb_print_string("This is a blue line.");

    // 防止内核返回
    while (1);
}
