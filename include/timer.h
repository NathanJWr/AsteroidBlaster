#ifndef TIMER_H
#define TIMER_H
#include <stdbool.h>
typedef struct _Timer {
        int start_time;
        int current_time;
        int delta;
        bool done;
} Timer;
Timer newTimer();
void updateTimer(Timer*);
bool isTimerDone(Timer);
#endif
