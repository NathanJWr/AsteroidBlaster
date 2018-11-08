#include "currency.h"
#include "sprite.h"
#include <stdlib.h>
#include <string.h>
extern int SCREEN_H;
Ruby makeRuby(int x, int y) {
        Ruby ruby;
        ruby.x = x;
        ruby.y = y;
        ruby.dy = 2;
        ruby.dx = 0;
        ruby.sizeX = 30;
        ruby.sizeY = 30;
        setupRubySprite(&ruby.sprite);
        return ruby;
}

bool moveRuby(Ruby* const r) {
        r -> y += r -> dy;
        if(r -> y > SCREEN_H) {
                return false;
        }
        else return true;
}

void generateCurrency(rubyVector* const v, int x, int y) {
        int p = rand() % 100 + 1;
        if(p >= 70) {
                rubyVector_add(v, makeRuby(x, y));
        }
}

void rubyVector_init(rubyVector* const v) {
        v->rubies = NULL;
        v->size = 0;
        v->count = 0;
}

void rubyVector_add(rubyVector* const v, Ruby b) {
        if(v->size == 0) {
                v->size = 10;
                v->rubies = (Ruby*) malloc(sizeof(b) * v->size);
                memset(v->rubies, '\0', sizeof(b) * v->size);
        }
        if(v->size == v->count) {
                v->size *= 2;
                v->rubies = (Ruby*) realloc(v->rubies, sizeof(b) * v->size);
        }
        v->rubies[v->count] = b;
        v->count++;
}

Ruby* rubyVector_get(rubyVector* const v, int index) {
        if(index >= v->size || index < 0) {
                exit(1);
        }
        return &(v->rubies[index]);
}

void rubyVector_erase(rubyVector* const v, int index) {
        int i;
        if(index >= v->size || index < 0) {
                exit(1);
        }
        destroySprite(&(v -> rubies[index].sprite));
        for(i = index; i < v -> count; i++) {
                v -> rubies[i] = v -> rubies[i+1];
        }
        v -> count--;
        printf("Ruby Erased\n");
}

void rubyVector_free(rubyVector* const v) {
        int i;
        for(i = 0; i < v -> count; i++) {
                destroySprite(&(v -> rubies[i].sprite));
                printf("Freed Ruby Texture\n");
        }
        free(v->rubies);
        v->size = 0;
        v->count = 0;
}
