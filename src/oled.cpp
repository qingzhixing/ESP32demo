#include "oled.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled_display(U8G2_CB_TYPE, OLED_RESET_PIN, OLED_CLOCK_PIN, OLED_DATA_PIN);

void oled_init()
{
    oled_display.begin();
    oled_display.setFont(u8g2_font_ncenB08_tr);
    oled_display.clearBuffer();
    oled_display.sendBuffer();
}