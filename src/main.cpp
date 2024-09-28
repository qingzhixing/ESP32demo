#include "main.h"
#include "debug.h"

hw_timer_t *timer = nullptr;
void serial_output();
void draw();

void IRAM_ATTR timer_interrupt_handler()
{
    encoder_update();
}

void timer_init()
{
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &timer_interrupt_handler, true);
    timerAlarmWrite(timer, 100ul, true);
    timerAlarmEnable(timer);
}

void serial_init()
{
    Serial.begin(115200);
    Serial.println("@qingzhixing");
}

void setup()
{
    led_init();
    led_on();
    oled_init();
    encoder_init();
    serial_init();
    timer_init();
}

void encoder_turned(bool direction)
{
    Serial.printf("encoder turned,direction: %s\n", direction ? "right" : "left");
    ui.circle_x += direction ? 1 : -1;
}

void loop()
{
    on_encoder_turned(encoder_turned);
    draw_frame();
}