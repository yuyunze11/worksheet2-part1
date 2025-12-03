
#include "../drivers/fb.h"   // 用 fb 驱动的接口，不再自己操作显存/IO

void kmain(void)
{
    fb_init();   // 初始化颜色、光标，并清屏（你在 fb.c 里已经这么写了）
    fb_clear();

    // 第一行：白字黑底
    fb_set_color(FB_WHITE, FB_BLACK);
    fb_move_cursor_xy(0, 0);
    fb_print_string("Task3 framebuffer test");

    // 第二行：白字蓝底
    fb_set_color(FB_WHITE, FB_BLUE);
    fb_move_cursor_xy(0, 1);
    fb_print_string("This is a blue line.");

    while (1) {
        // 死循环，防止内核返回
    }
}

