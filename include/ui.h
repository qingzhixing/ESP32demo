#pragma once
#ifndef _UI_H
#define _UI_H

#include "oled.h"
#include "encoder.h"

struct UI
{
    uint8_t circle_r = 5;
    uint8_t circle_x = OLED_WIDTH / 2;
    uint8_t circle_y = OLED_HEIGHT - circle_r - 5;

    void init();
    void update_frame();
    void draw_circle();
};

extern UI ui;

#endif // !_UI_H