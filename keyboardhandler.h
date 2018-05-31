#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <SDL2/SDL.h>
#include <map>
class KeyboardHandler {
        public:
                KeyboardHandler();
                void handleKeyboardEvent(SDL_Event& e);
                bool isPressed(char keycode);
                void resetPresses();
                void resetShot();
        private:
                bool keyW;
                bool keyS;
                bool keyA;
                bool keyD;
                std::map<char, bool> keycodes;
};

#endif
