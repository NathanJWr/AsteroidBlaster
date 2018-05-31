#ifndef BULLET_H
#define BULLET_H
class Bullet {
        public:
                Bullet(int x, int y, int dx, int dy);
                const int getXPos() const;
                const int getYPos() const;
                void move();

        private:
                int xPos;
                int yPos;
                int dx;
                int dy;
};
#endif
