#include "encoder.h"
#include <Arduino.h>

static void empty_key_callback() {}
static void empty_turn_callback(bool) {}

void Encoder::on_pressed(EncoderKeyCallback callback)
{
    on_encoder_press_callback = callback;
}

void Encoder::on_released(EncoderKeyCallback callback)
{
    on_encoder_release_callback = callback;
}

void Encoder::on_turned(EncoderTurnCallback callback)
{
    on_encoder_turn_callback = callback;
}

void key_interrupt_handler()
{
    static auto encoder = Encoder::get_instance();
    if (encoder.is_pressed())
    {
        encoder.on_encoder_press_callback();
    }
    else
    {
        encoder.on_encoder_release_callback();
    }
}

void Encoder::init()
{
    pinMode(ENCODER_S1, INPUT_PULLUP);
    pinMode(ENCODER_S2, INPUT_PULLUP);
    pinMode(ENCODER_KEY, INPUT_PULLUP);

    encoder_state = digitalRead(ENCODER_S1);
    encoder_last_state = encoder_state;

    on_encoder_press_callback = empty_key_callback;
    on_encoder_release_callback = empty_key_callback;
    on_encoder_turn_callback = empty_turn_callback;

    attachInterrupt(digitalPinToInterrupt(ENCODER_KEY), key_interrupt_handler, CHANGE);
}

bool Encoder::update()
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

bool Encoder::is_pressed() const
{
    return digitalRead(ENCODER_KEY) == ENCODER_KEY_PRESSED_LEVEL;
}