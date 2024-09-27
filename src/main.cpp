#include "main.h"
#include "debug.h"

static Screen screen;

hw_timer_t *timer = nullptr;
void serial_output();
void draw();

void IRAM_ATTR timer_interrupt_handler()
{
    return;
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

int16_t circle_r = 5;
int16_t delta_x = 0;
int16_t circle_x = 128 / 2;
int16_t circle_y = 64 - circle_r - 5;
void draw()
{
    auto display = get_oled_display();
    display.print("Hello World!");
    display.clearBuffer();
    display.drawCircle(circle_x + delta_x, circle_y, circle_r);
    display.sendBuffer();
}

void encoder_turned(bool direction)
{
    Serial.printf("encoder turned,direction: %s\n", direction ? "right" : "left");
    delta_x += direction ? 1 : -1;
}

void loop()
{
    on_encoder_turned(encoder_turned);
    draw();
}