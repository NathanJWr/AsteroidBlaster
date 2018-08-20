#include <SDL2/SDL.h>
#include "timer.h"
struct Timer newTimer(int delta) {
        printf("New Timer Started!\n");
        struct Timer timer;
        timer.start_time = SDL_GetTicks();
        timer.current_time = SDL_GetTicks();
        timer.delta = delta;
        timer.done = false;
        return timer;
}
void updateTimer(struct Timer* timer) {
       timer -> current_time = SDL_GetTicks();
}

bool isTimerDone(struct Timer timer) {
        if(timer.current_time - timer.start_time >= timer.delta) {
                return true;
        }
        else return false;
}
