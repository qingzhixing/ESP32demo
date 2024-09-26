#include "oled.h"

static U8G2 u8g2;
const U8G2 &oled_init()
{
    u8g2 = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_CB_TYPE, OLED_CLOCK_PIN, OLED_DATA_PIN, OLED_RESET_PIN);

    u8g2.begin();

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.sendBuffer();

    return u8g2;
}

const U8G2 &get_u8g2()
{
    return u8g2;
}