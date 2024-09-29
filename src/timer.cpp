#include "timer.h"
#include <Arduino.h>
#include <list>

static std::list<void (*)()> timer_update_list;

static hw_timer_t *timer = nullptr;

static void IRAM_ATTR timer_interrupt_handler()
{
    for (auto func : timer_update_list)
    {
        func();
    }
}

void timer_init()
{
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &timer_interrupt_handler, true);
    timerAlarmWrite(timer, 100ul, true);
    timerAlarmEnable(timer);
}

void register_timer_update(void (*func)())
{
    timer_update_list.push_back(func);
}

void deregister_timer_update(void (*func)())
{
    timer_update_list.remove(func);
}
