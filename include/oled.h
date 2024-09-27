#pragma once
#ifndef _OLED_H
#define _OLED_H

#include <U8g2lib.h>

#define U8G2_CB_TYPE U8G2_R0
#define OLED_CLOCK_PIN SCL
#define OLED_DATA_PIN SDA
#define OLED_RESET_PIN U8X8_PIN_NONE

 U8G2 oled_init();

/*
 * This function is used to get the global U8G2 object.
 * WARNING: This function should only be called after the OLED has been initialize!!!
 */
 U8G2 get_u8g2();
#endif // !_OLED_H