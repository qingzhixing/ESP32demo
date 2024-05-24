
#include <Arduino.h>
#include <U8g2lib.h>

#define LED_PIN GPIO_NUM_2
#define ENCODER_KEY GPIO_NUM_15
#define ENCODER_S1 GPIO_NUM_16
#define ENCODER_S2 GPIO_NUM_4

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);

static int16_t encoder_last_state;
static int16_t encoder_state;
static int16_t encoder_count;

static bool led_state = LOW;
static bool enable_screen = true;

void setup()
{
    u8g2.begin();
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(ENCODER_KEY, INPUT_PULLUP);
    pinMode(ENCODER_S1, INPUT_PULLUP);
    pinMode(ENCODER_S2, INPUT_PULLUP);
    digitalWrite(LED_PIN, led_state);
    delay(1000);

    encoder_state = digitalRead(ENCODER_S1);
    encoder_last_state = encoder_state;
    encoder_count = 0;
}

void toggle_led()
{
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
}
void toggle_screen()
{
    enable_screen = !enable_screen;
    if (enable_screen)
    {
        u8g2.sleepOff();
    }
    else
    {
        u8g2.sleepOn();
    }
}

static bool need_serial_output = false;
void serial_output()
{
    if (!need_serial_output)
        return;
    need_serial_output = false;
    Serial.printf("Count: %d, Value: %d\r\n", encoder_count, encoder_count / 2);
    Serial.printf("LED State: %s\r\n", led_state ? "ON" : "OFF");
    Serial.printf("Screen State: %s\r\n", enable_screen ? "ON" : "OFF");
}

void screen_output()
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Encoder Value:");
    u8g2.setCursor(40, 10);
    u8g2.print(encoder_count / 2);
    u8g2.drawStr(0, 30, "LED State:");
    u8g2.setCursor(40, 30);
    u8g2.print(led_state ? "ON" : "OFF");
    u8g2.drawStr(0, 50, "Screen State:");
    u8g2.sendBuffer();
}

void loop()
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
    }
    encoder_last_state = encoder_state;

    if (digitalRead(ENCODER_KEY) == LOW)
    {
        toggle_led();
        toggle_screen();
        while (digitalRead(ENCODER_KEY) == LOW)
        {
            delay(10);
        }
    }
}