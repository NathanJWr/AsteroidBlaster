#include "player.h"
#include "bullet.h"
Player::Player(const int SCREEN_W, const int SCREEN_H) : 
        xPos(SCREEN_W / 2),
        yPos(SCREEN_H / 2),
        dx(5),
        dy(5),
        sizeX(30),
        sizeY(30)
{
}

void Player::shoot() {
       bullets.push_back(Bullet(xPos, yPos, dx+10, dy+10)); 
}

void Player::moveBullets(int SCREEN_H, int SCREEN_W) {
        for(int i = 0; i < (int)bullets.size(); i++) {
                if(bullets.at(i).getXPos() > SCREEN_W 
                                || bullets.at(i).getXPos() < 0) {
                        bullets.erase(bullets.begin() + i);
                }
                if(bullets.at(i).getYPos() > SCREEN_H 
                                || bullets.at(i).getYPos() < 0) {
                        bullets.erase(bullets.begin() + i);
                }
                bullets.at(i).move();
        }
}

const std::vector<Bullet> Player::getShots() const {
        return bullets;
}

const int Player::getXPos() const {
        return xPos;
}
const int Player::getYPos() const {
        return yPos;
}

const int Player::getSizeX() const {
        return sizeX;
}

const int Player::getSizeY() const {
        return sizeY;
}

void Player::moveUp() {
        yPos -= dy;
}

void Player::moveDown() {
        yPos += dy;
}

void Player::moveRight() {
        xPos += dx;
}

void Player::moveLeft() {
        xPos -= dx;
}
