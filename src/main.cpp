#include "main.h"

void serial_init()
{
    Serial.begin(115200);
    Serial.println("@qingzhixing");
}

void setup()
{
    led_init();
    led_on();
    encoder_init();
    serial_init();
    timer_init();
    ui.init();

    register_timer_update(encoder_update);
}

void loop()
{
    ui.update_frame();
}