#ifndef _TICK_H_
#define _TICK_H_

void timer_init(void);

void register_timer_update(void (*func)());

void deregister_timer_update(void (*func)());

#endif // !_TICK_H_