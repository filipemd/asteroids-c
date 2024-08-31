#include <raylib.h>

#include "timer.h"

void start_timer(Timer *timer, double lifetime) {
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool timer_done(Timer* timer) {
    return GetTime() - timer->startTime >= timer->lifeTime;
}

void stop_timer(Timer *timer) {
    timer->lifeTime = 0;
}

double get_elapsed(Timer* timer) {
    return GetTime() - timer->startTime;
}
