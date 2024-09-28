#pragma once
#ifndef _UI_H
#define _UI_H

#include "oled.h"
#include "encoder.h"

struct Screen
{
    static const int width = 128;
    static const int height = 64;
};

struct UI
{
    uint8_t circle_r = 5;
    uint8_t circle_x = 64;
    uint8_t circle_y = 64 - circle_r - 5;
};
extern UI ui;

void draw_frame();

#endif // !_UI_H