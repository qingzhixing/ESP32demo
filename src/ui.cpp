#include "ui.h"

UI ui;

static void encoder_turned(bool direction)
{
    static bool odd = false;
    static bool last_direction = false;

    odd = !odd;
    bool current_direction = get_encoder_turn_direction();

    if (odd || last_direction != current_direction)
    {
        last_direction = current_direction;
        return;
    }

    Serial.printf("encoder turned,direction: %s\n", direction ? "right" : "left");

    ui.circle_x += direction ? 1 : -1;
    last_direction = current_direction;
}

void UI::init()
{
    oled_init();
    on_encoder_turned(encoder_turned);
}

void UI::draw_circle()
{
    oled_display.drawCircle(ui.circle_x, ui.circle_y, ui.circle_r);

    // 判断绘制边界
    if (ui.circle_x < ui.circle_r) // circle_x - circle_r < int(0)
    {
        oled_display.drawCircle(OLED_WIDTH + ui.circle_x, ui.circle_y, ui.circle_r);
    }
    else if (ui.circle_x + ui.circle_r > OLED_WIDTH)
    {
        oled_display.drawCircle(0 - ui.circle_r + (ui.circle_x + ui.circle_r - OLED_WIDTH), ui.circle_y, ui.circle_r);
    }

    // 圆心边界
    if (ui.circle_x >= OLED_WIDTH)
    {
        if (get_encoder_turn_direction() == ENCODER_CLOCKWISE)
        {
            ui.circle_x = 0;
        }
        else
        {
            ui.circle_x = OLED_WIDTH - ui.circle_r + 1;
        }
    }
}

void UI::update_frame()
{
    oled_display.clearBuffer();
    oled_display.drawStr(0, 10, "Hello, QZX!");

    draw_circle();

    oled_display.sendBuffer();
}