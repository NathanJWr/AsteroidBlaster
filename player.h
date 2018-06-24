#ifndef PLAYER_H
#define PLAYER_H
struct Player {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
};

void playerMoveUp(struct Player*);
void playerMoveDown(struct Player*);
void playerMoveLeft(struct Player*);
void playerMoveRight(struct Player*);
#endif
