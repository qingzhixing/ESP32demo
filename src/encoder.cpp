#include "encoder.h"
#include <Arduino.h>

static int16_t encoder_last_state;
static int16_t encoder_state;
static EncoderKeyCallback on_encoder_press_callback;
static EncoderKeyCallback on_encoder_release_callback;
static EncoderTurnCallback on_encoder_turn_callback;

static void empty_key_callback() {}
static void empty_turn_callback(bool) {}

void set_on_encoder_press(EncoderKeyCallback callback)
{
    on_encoder_press_callback = callback;
}

void set_on_encoder_release(EncoderKeyCallback callback)
{
    on_encoder_release_callback = callback;
}

void set_on_encoder_turn(EncoderTurnCallback callback)
{
    on_encoder_turn_callback = callback;
}

static void encoder_key_interrupt_handler()
{
    if (is_encoder_pressed())
    {
        on_encoder_press_callback();
    }
    else
    {
        on_encoder_release_callback();
    }
}

void encoder_init()
{
    pinMode(ENCODER_S1, INPUT_PULLUP);
    pinMode(ENCODER_S2, INPUT_PULLUP);
    pinMode(ENCODER_KEY, INPUT_PULLUP);

    encoder_state = digitalRead(ENCODER_S1);
    encoder_last_state = encoder_state;

    on_encoder_press_callback = empty_key_callback;
    on_encoder_release_callback = empty_key_callback;
    on_encoder_turn_callback = empty_turn_callback;

    attachInterrupt(digitalPinToInterrupt(ENCODER_KEY), encoder_key_interrupt_handler, CHANGE);
}

bool update_encoder()
{
    bool updated = false;
    encoder_state = digitalRead(ENCODER_S1);
    if (encoder_state != encoder_last_state)
    {
        // clockwise turn
        if (digitalRead(ENCODER_S2) == encoder_state)
        {
            on_encoder_turn_callback(true);
        }
        // counterclockwise turn
        else
        {
            on_encoder_turn_callback(false);
        }
        updated = true;
    }
    encoder_last_state = encoder_state;
    return updated;
}

bool is_encoder_pressed()
{
    return digitalRead(ENCODER_KEY) == ENCODER_KEY_PRESSED_LEVEL;
}