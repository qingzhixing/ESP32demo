#include "ui.h"
UI ui;
void draw_frame()
{
    oled_display.clearBuffer();
    oled_display.drawStr(0, 10, "Hello, QZX!");
    oled_display.drawCircle(ui.circle_x, ui.circle_y, ui.circle_r);

    // 判断绘制边界
    if (ui.circle_x - ui.circle_r < 0)
    {
        oled_display.drawCircle(Screen::width + ui.circle_r - (ui.circle_x - ui.circle_r), ui.circle_y, ui.circle_r);
    }
    else if (ui.circle_x + ui.circle_r > Screen::width)
    {
        oled_display.drawCircle(0 - ui.circle_r + (ui.circle_x + ui.circle_r - Screen::width), ui.circle_y, ui.circle_r);
    }

    // 圆心边界
    if (ui.circle_x > Screen::width)
    {
        if (get_encoder_turn_direction() == ENCODER_CLOCKWISE)
        {
            ui.circle_x = 0;
        }
        else
        {
            ui.circle_x = Screen::width - ui.circle_r;
        }
    }
    oled_display.sendBuffer();
}