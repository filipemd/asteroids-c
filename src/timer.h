#ifndef DELAY_H
#define DELAY_H

typedef struct timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;

void start_timer(Timer *timer, double lifetime);
bool timer_done(Timer* timer);
void stop_timer(Timer* timer);

double get_elapsed(Timer* timer);

#endif
