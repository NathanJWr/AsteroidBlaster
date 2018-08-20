#include <stdbool.h>
#include "gamelogic.h"
#include "timer.h"
struct Timer player_invuln_time;
void gameTick(asteroidVector* asteroidV,
                bulletVector* bulletV,
                struct Player* player,
                struct KeyPresses* keys,
                const int SCREEN_H) {

        movePlayer(keys, player, bulletV);
        for(int i = 0; i < asteroidV -> count; i++) {
                if(!moveAsteroid(&(asteroidV->asteroids[i]), SCREEN_H)) {
                        asteroidVector_erase(asteroidV, i);
                }
        }

        //Bullet Collision
        for(int i = 0; i < bulletV -> count; i++) {
                if(!moveBullet(&(bulletV -> bullets[i]), SCREEN_H)) {
                        bulletVector_erase(bulletV, i);
                }
                for(int j = 0; j < asteroidV -> count; j++) {
                        if(checkCollision_bullet(*asteroidVector_get(asteroidV, j),
                                                *bulletVector_get(bulletV, i))) {
                                asteroidV -> asteroids[j].hit = true;
                                bulletVector_erase(bulletV , i);
                                player -> score++;
                        }
                }
        }

        //Player Collision
        for(int i = 0; i < asteroidV -> count; i++) {
                if(checkCollision_player(*asteroidVector_get(asteroidV, i), *player)
                                && !asteroidV -> asteroids[i].hit && !player -> hit) {
                              
                        player -> hit = true;
                        player -> lives -= 1;
                        player_invuln_time = newTimer(2000);
                }
        }
        if(player -> hit) {
                updateTimer(&player_invuln_time);
                if(isTimerDone(player_invuln_time)) {
                        player -> hit = false;
                }
        }

        //Laser charging
        player -> laser_percent++;
        if(player -> laser_percent < 0) {
                player -> laser_percent = 0;
        }
        if(player -> laser_percent > 100) {
                player -> laser_percent = 100;
        }

}
bool handleEvents(SDL_Event* e, struct KeyPresses* k) {
        while(SDL_PollEvent(e) != 0) {
                if(e -> type == SDL_QUIT) {
                        return false;
                }
                if(e -> type == SDL_KEYDOWN) {
                        switch(e -> key.keysym.sym) {
                                case SDLK_w:
                                        k -> w = true;
                                        k -> s = false;
                                        k -> a = false;
                                        k -> d = false;
                                        break;
                                case SDLK_a:
                                        k -> a = true;
                                        k -> d = false;
                                        k -> w = false;
                                        k -> s = false;
                                        break;
                                case SDLK_s:
                                        k -> s = true;
                                        k -> w = false;
                                        k -> a = false;
                                        k -> d = false;
                                        break;
                                case SDLK_d:
                                        k -> d = true;
                                        k -> a = false;
                                        k -> w = false;
                                        k -> s = false;
                                        break;
                                case SDLK_SPACE:
                                        k -> space = true;
                                        break;
                                case SDLK_ESCAPE:
                                        k -> escape = true;
                                        break;
                        }
                }
        }
        return true;
}
void movePlayer(struct KeyPresses* k, struct Player* p, bulletVector* bv) {
        if(k -> w) {
                playerMoveUp(p);
        }
        if(k -> a) {
                playerMoveLeft(p);
        }
        if(k -> s) {
                playerMoveDown(p);
        }
        if(k -> d) {
                playerMoveRight(p);
        }
        if(k -> space) {
                if(p -> laser_percent >= 33) {
                        bulletVector_add(bv, makeBullet(p -> x + (p -> sizeX / 2), p -> y));
                        p -> laser_percent -= 33;
                }
                k -> space = false;
        }
}


bool checkCollision_bullet(struct Asteroid asteroid, struct Bullet bullet) {
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        leftA = bullet.hitX;
        rightA = bullet.hitX + bullet.hitW;
        topA = bullet.hitY;
        bottomA = bullet.hitY + bullet.hitH;

        leftB = asteroid.hitX;
        rightB = asteroid.hitX + asteroid.hitW;
        topB = asteroid.hitY;
        bottomB = asteroid.hitY + asteroid.hitH;

        if(bottomA >= topB
                        && topA <= bottomB
                        && rightA >= leftB
                        && leftA <= rightB
                        && !asteroid.hit) {
                return true;
        }
        else return false;
}

bool checkCollision_player(struct Asteroid asteroid, struct Player player) {
        int leftP, leftB;
        int rightP, rightB;
        int topP, topB;
        int bottomP, bottomB;

        leftP = player.hitX;
        rightP = player.hitX + player.hitW;
        topP = player.hitY;
        bottomP = player.hitY + player.hitH;

        leftB = asteroid.hitX;
        rightB = asteroid.hitX + asteroid.hitW;
        topB = asteroid.hitY;
        bottomB = asteroid.hitY + asteroid.hitH;
        if(bottomP >= topB
                        && topP <= bottomB
                        && rightP >= leftB
                        && leftP <= rightB
                        ) {
                printf("HIT!\n");
                printf("%d\n", player.lives);
                return true;
        }
        return false;
}
