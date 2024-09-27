#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <U8g2lib.h>

struct Screen
{
    const int width = 128;
    const int height = 64;
    U8G2 display;
    Screen(const U8G2 &display) : display(display) {}
};

#endif // !_SCREEN_H_