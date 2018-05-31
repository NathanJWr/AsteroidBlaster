#include "bullet.h"

Bullet::Bullet(int x, int y, int dx, int dy) :
        xPos(x),
        yPos(y),
        dx(dx),
        dy(dy) {
}

const int Bullet::getXPos() const {
        return xPos;
}

const int Bullet::getYPos() const {
        return yPos;
}

void Bullet::move() {
        yPos -= dy;
}
