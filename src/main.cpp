#include "main.h"

int16_t encoder_last_state;
int16_t encoder_state;
int16_t encoder_count;

bool need_screen_output = true;
bool need_serial_output = false;

hw_timer_t *timer = nullptr;
void serial_output();
void screen_output();

void IRAM_ATTR timer_interrupt_handler()
{
    encoder_state = digitalRead(ENCODER_S1);
    if (encoder_state != encoder_last_state)
    {
        if (digitalRead(ENCODER_S2) == encoder_state)
        {
            encoder_count++;
        }
        else
        {
            encoder_count--;
        }
        need_serial_output = true;
    }
    encoder_last_state = encoder_state;
}

void encoder_init()
{
    pinMode(ENCODER_S1, INPUT_PULLUP);
    pinMode(ENCODER_S2, INPUT_PULLUP);

    encoder_state = digitalRead(ENCODER_S1);
    encoder_last_state = encoder_state;
    encoder_count = 0;
}

void key_init()
{
    pinMode(ENCODER_KEY, INPUT_PULLUP);
}

void serial_init()
{

    Serial.begin(115200);
    Serial.println("qingzhixing sama!");
}

void timer_init()
{
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &timer_interrupt_handler, true);
    timerAlarmWrite(timer, 100ul, true);
    timerAlarmEnable(timer);
}

void setup()
{
    oled_init();
    encoder_init();
    led_init();
    key_init();
    serial_init();
    timer_init();
}

void serial_output()
{
    if (!need_serial_output)
        return;
    need_serial_output = false;
    Serial.printf("Count: %d, Value: %d\r\n", encoder_count, int(encoder_count / 2));
    Serial.printf("LED State: %s\r\n", get_led_state() == LOW ? "OFF" : "ON");
    Serial.printf("Screen Output: %s\r\n", need_screen_output ? "ON" : "OFF");
}

void screen_output()
{
    auto u8g2 = get_u8g2();
    u8g2.clearBuffer();
    if (!need_screen_output)
        return;
    u8g2.drawStr(0, 10, "Encoder Value:");
    u8g2.setCursor(100, 10);
    u8g2.print(int(encoder_count / 2));
    u8g2.drawStr(0, 30, "LED State:");
    u8g2.setCursor(100, 30);
    u8g2.print(get_led_state() == LOW ? "OFF" : "ON");
    u8g2.sendBuffer();
}

void loop()
{
    serial_output();
    screen_output();

    if (digitalRead(ENCODER_KEY) == LOW)
    {
        led_toggle();
        need_serial_output = true;
        while (digitalRead(ENCODER_KEY) == LOW)
            delay(10);
    }
}