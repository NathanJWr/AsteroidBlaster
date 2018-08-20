#ifndef TIMER_H
#define TIMER_H
#include <stdbool.h>
struct Timer {
        int start_time;
        int current_time;
        int delta;
        bool done;
};
struct Timer newTimer();
void updateTimer(struct Timer*);
bool isTimerDone(struct Timer);
#endif
