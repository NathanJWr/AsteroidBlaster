#include <stdbool.h>
#include "gamelogic.h"
#include "timer.h"
#include "currency.h"
Timer player_invuln_time;
Timer laser_recharge_time;
void splitLaser(bulletVector*, Player, int, int);
void gameTick(asteroidVector* const asteroidV,
                bulletVector* const bulletV,
                rubyVector* const rubyV,
                Player* const player,
                struct KeyPresses* const keys,
                const int SCREEN_H) {

        movePlayer(keys, player, bulletV);
        for(int i = 0; i < asteroidV -> count; i++) {
                if(!moveAsteroid(&(asteroidV->asteroids[i]), SCREEN_H)) {
                        asteroidVector_erase(asteroidV, i);
                }
        }

        //Bullet Collision
        for(int i = 0; i < bulletV -> count; i++) {
                if(!moveBullet(&(bulletV -> bullets[i]))) {
                        bulletVector_erase(bulletV, i);
                }
                for(int j = 0; j < asteroidV -> count; j++) {
                        if(checkCollision_bullet(*asteroidVector_get(asteroidV, j),
                                                bulletVector_get(bulletV, i))) {
                                asteroidV -> asteroids[j].hit = true;
                                Bullet b = bulletVector_get(bulletV, i);
                                bulletVector_erase(bulletV , i);
                                player -> score++;
                                splitLaser(bulletV, *player, b.x, b.y);
                                generateCurrency(rubyV, b.x, b.y);
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

        //Ruby Collision
        for(int i = 0; i < rubyV -> count; i++) {
                if(!moveRuby(&(rubyV -> rubies[i]))) {
                        rubyVector_erase(rubyV, i);
                }
                else if(checkCollision_ruby(*rubyVector_get(rubyV, i), *player)) {
                        player -> currency++;
                        rubyVector_erase(rubyV, i);
                }
        }

        //Laser charging
        if(isTimerDone(laser_recharge_time)) {
                laser_recharge_time = newTimer(100 / player -> laser_regen);
                player -> laser_percent += 2;
                if(player -> laser_percent > 100) {
                        player -> laser_percent = 100;
                }
        }
        updateTimer(&laser_recharge_time);
}
bool handleEvents(SDL_Event* const e, struct KeyPresses* const k) {
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
void movePlayer(struct KeyPresses* const k,
                Player* const p,
                bulletVector* const bv) {

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
                if(p -> laser_percent >= p -> laser_cost) {
                        bulletVector_add(bv, makeBullet(p -> x + (p -> sizeX / 2), p -> y, 0, 3));
                        p -> laser_percent -= p -> laser_cost;
                }
                k -> space = false;
        }
}

bool checkCollision_bullet(Asteroid asteroid, Bullet bullet) {
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

bool checkCollision_player(Asteroid asteroid, Player player) {
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
                return true;
        }
        return false;
}
bool checkCollision_ruby(Ruby r, Player p) {
        int leftR, leftP;
        int rightR, rightP;
        int topR, topP;
        int bottomR, bottomP;

        leftP = p.hitX;
        rightP = p.hitX + p.hitW;
        topP = p.hitY;
        bottomP = p.hitY + p.hitH;

        leftR = r.x;
        rightR = r.x + r.sizeX;
        topR = r.y;
        bottomR = r.y +r.sizeY;

        if(bottomP >= topR
                        && topP <= bottomR
                        && rightP >= leftR
                        && leftP <= rightR
                        ) {
                return true;
        }
        return false;

}
void splitLaser(bulletVector* const vec, Player p, int x, int y) {
        if(p.split_laser) {
                bulletVector_add(vec,
                                makeBullet(x,
                                        y, 3, 0));
                bulletVector_add(vec,
                                makeBullet(x,
                                        y, -3, 0));
        }
}

