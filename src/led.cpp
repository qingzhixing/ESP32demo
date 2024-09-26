#include "led.h"
#include <Arduino.h>

static bool led_state = LOW;

void led_init()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, led_state);
}

void led_toggle()
{
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
}

void led_on()
{
    led_state = HIGH;
    digitalWrite(LED_PIN, led_state);
}

void led_off()
{
    led_state = LOW;
    digitalWrite(LED_PIN, led_state);
}

bool get_led_state()
{
    return led_state;
}