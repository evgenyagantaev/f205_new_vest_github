#ifndef TIMER_250HZ_INTERFACE_H
#define TIMER_250HZ_INTERFACE_H

void timer_250hz_object_init();

void timer_250hz_flag_set();
void timer_250hz_flag_reset();
int timer_250hz_flag_get();

void timer_250hz_start();
void timer_250hz_action();

uint32_t timer_250hz_get_tick();

#endif // TIMER_250HZ_INTERFACE_H
