#include "oled.h"

static U8G2 *u8g2;
U8G2 oled_init()
{
    auto display = get_u8g2();

    display.begin();

    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.sendBuffer();

    return std::move(display);
}

U8G2 get_u8g2()
{
    if (u8g2 == nullptr)
    {
        u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_CB_TYPE, OLED_CLOCK_PIN, OLED_DATA_PIN, OLED_RESET_PIN);
    }

    return *u8g2;
}