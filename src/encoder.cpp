#include "encoder.h"
#include <Arduino.h>

int16_t encoder_last_state;
int16_t encoder_state;
int16_t encoder_count;

void encoder_init()
{
    pinMode(ENCODER_S1, INPUT_PULLUP);
    pinMode(ENCODER_S2, INPUT_PULLUP);
    pinMode(ENCODER_KEY, INPUT_PULLUP);

    encoder_state = digitalRead(ENCODER_S1);
    encoder_last_state = encoder_state;
    encoder_count = 0;
}

bool update_encoder()
{
    bool updated = false;
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
        updated = true;
    }
    encoder_last_state = encoder_state;
    return updated;
}