#include "oled.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled_display = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_CB_TYPE, OLED_RESET_PIN, OLED_CLOCK_PIN, OLED_DATA_PIN);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C get_oled_display()
{
    static auto display = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_CB_TYPE, OLED_RESET_PIN, OLED_CLOCK_PIN, OLED_DATA_PIN);
    return display;
}

void oled_init()
{
    auto display = get_oled_display();
    display.begin();

    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.sendBuffer();
}