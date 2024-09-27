#pragma once
#ifndef _OLED_H
#define _OLED_H

#include <U8g2lib.h>

#define U8G2_CB_TYPE U8G2_R0
#define OLED_CLOCK_PIN SCL
#define OLED_DATA_PIN SDA
#define OLED_RESET_PIN U8X8_PIN_NONE

void oled_init();
U8G2_SSD1306_128X64_NONAME_F_HW_I2C &get_oled_display();

struct Screen
{
    const int width = 128;
    const int height = 64;
};
#endif // !_OLED_H