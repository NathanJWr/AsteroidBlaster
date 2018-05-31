#ifndef BLOCK_H
#define BLOCK_H
class Block {
        public:
                Block(const int SCREEN_W, const int SCREEN_H);
                void move();
                const int getXPos() const;
                const int getYPos() const;
                const int getSizeX() const;
                const int getSizeY() const;
        private:
                int xPos;
                int yPos;
                int sizeX;
                int sizeY;
                int dy;
};
#endif

