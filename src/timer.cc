#include <SDL2/SDL.h>
#include "timer.h"
Timer newTimer(int delta) {
  Timer timer;
  timer.start_time = SDL_GetTicks();
  timer.current_time = SDL_GetTicks();
  timer.delta = delta;
  timer.done = false;
  return timer;
}
void updateTimer(Timer* const timer) {
       timer -> current_time = SDL_GetTicks();
}

bool isTimerDone(Timer timer) {
  if(timer.current_time - timer.start_time >= timer.delta) {
    return true;
  }
  else return false;
}
