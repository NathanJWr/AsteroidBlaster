#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "bullet.h"
class Player {
        public:
                Player(const int SCREEN_W, const int SCREEN_H);
                const int getXPos() const;
                const int getYPos() const;
                const int getSizeX() const;
                const int getSizeY() const;
                const std::vector<Bullet> getShots() const;
                void moveUp();
                void moveDown();
                void moveLeft();
                void moveRight();
                void moveBullets(int SCREEN_H, int SCREEN_W);

                void shoot();

        private:
                std::vector<Bullet> bullets;
                int xPos;
                int yPos;
                int dx;
                int dy;
                int sizeX;
                int sizeY;
};
#endif
