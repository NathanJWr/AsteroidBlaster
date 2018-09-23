#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
        struct Display_Objects {
                SDL_Texture* ruby;
                SDL_Texture* curr;
                bool ruby_init;
                int currency;
        };
        bool initVideo();
        void killVideo();
        void initDisplayObjects();
        void cleanDisplayObjects();
        SDL_Texture* surfaceToTexture(SDL_Surface*);
        SDL_Texture* surfaceToTextureSafe(SDL_Surface*);
        SDL_Texture* createTextTexture(TTF_Font*, char*, SDL_Color);
        SDL_Texture* createTextTextureWrapped(TTF_Font*, char*, SDL_Color, int);
        SDL_Texture* loadImageTexture(char*);
        SDL_Surface* loadImageSurface(char*);
        void renderTexture(SDL_Texture*, SDL_Rect*, SDL_Rect*);
        void setDrawColor(SDL_Color);
        void renderTextBox(int, int, char*);
        void renderRectangleOutline(SDL_Rect*);
        void renderRectangleFull(SDL_Rect*);
        void renderPresent();
        void clearRender();
#endif
