#include "main.h"

static Screen screen(get_u8g2());
static Encoder encoder;

hw_timer_t *timer = nullptr;
void serial_output();
void draw();

void IRAM_ATTR timer_interrupt_handler()
{
    encoder.update();
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
    oled_init();
    encoder.init();
    led_init();
    timer_init();
    serial_init();
}

int16_t circle_r = 5;
int16_t delta_x = 0;
int16_t circle_x = 128 / 2;
int16_t circle_y = 64 - circle_r - 5;
void draw()
{
    auto u8g2 = screen.display;
    u8g2.clearBuffer();
    u8g2.drawCircle(circle_x + delta_x, circle_y, circle_r);
    u8g2.sendBuffer();
}

void encoder_turned(bool direction)
{
    delta_x += direction ? 1 : -1;
}

void loop()
{
    encoder.on_turned(encoder_turned);
    draw();
}