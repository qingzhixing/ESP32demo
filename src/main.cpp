#include "main.h"
#include "debug.h"

static Screen screen;

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

uint8_t circle_r = 5;
int8_t delta_x = 0;
uint8_t circle_x = 128 / 2;
uint8_t circle_y = 64 - circle_r - 5;
void draw()
{
    oled_display.clearBuffer();
    oled_display.drawStr(0, 10, "Hello, QZX!");
    oled_display.drawCircle(abs(circle_x + delta_x), circle_y, circle_r);
    oled_display.sendBuffer();
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