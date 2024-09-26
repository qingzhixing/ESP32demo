#ifndef _LED_H
#define _LED_H

#define LED_PIN GPIO_NUM_2

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);
bool get_led_state(void);

#endif // !_LED_H