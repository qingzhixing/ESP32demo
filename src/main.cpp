#include "main.h"

static Screen *screen = nullptr;

hw_timer_t *timer = nullptr;
void serial_output();
void screen_output();

void IRAM_ATTR timer_interrupt_handler()
{
    update_encoder();
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
    encoder_init();
    led_init();
    timer_init();
    serial_init();
}

int16_t circle_r = 5;
int16_t delta_x = 0;
int16_t circle_x = 128 / 2;
int16_t circle_y = 64 - circle_r - 5;
void screen_output()
{
    auto u8g2 = get_u8g2();
    u8g2.clearBuffer();
    // u8g2.drawCircle(circle_x + delta_x, circle_y, circle_r);
    u8g2.drawFilledEllipse(circle_x + delta_x, circle_y, circle_r, circle_r);
    u8g2.sendBuffer();
}

void loop()
{
    screen_output();

    if (digitalRead(ENCODER_KEY) == LOW)
    {
        led_toggle();
        while (digitalRead(ENCODER_KEY) == LOW)
            delay(10);
    }
}