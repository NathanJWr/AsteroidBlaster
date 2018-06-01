#include "keyboardhandler.h"

KeyboardHandler::KeyboardHandler() {
        keycodes['w']=false;
        keycodes['s']=false;
        keycodes['a']=false;
        keycodes['d']=false;
        keycodes[' ']=false;

}
void KeyboardHandler::handleKeyboardEvent(SDL_Event& e) {
       while(SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN) {
               switch(e.key.keysym.sym) {
                       case SDLK_w:
                               keycodes['w'] = true;
                               keycodes['s'] = false;
                               break;
                       case SDLK_s:
                               keycodes['s'] = true;
                               keycodes['w'] = false;
                               break;
                       case SDLK_a:
                               keycodes['a'] = true;
                               keycodes['d'] = false;
                               break;
                       case SDLK_d:
                               keycodes['d'] = true;
                               keycodes['a'] = false;
                               break;
                       case SDLK_SPACE:
                               keycodes[' '] = true;
                               break;
               }
       }
}

bool KeyboardHandler::isPressed(char keycode) {
        return keycodes[keycode];
}

void KeyboardHandler::resetPresses() {
        keycodes['w'] = false;
        keycodes['s'] = false;
        keycodes['a'] = false;
        keycodes['d'] = false;
}

void KeyboardHandler::resetShot() {
        keycodes[' ']=false;
}
