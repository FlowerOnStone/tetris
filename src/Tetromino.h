#ifndef TETROMINO__H
#define TETROMINO__H

#include "Header.h"
#include "Block.h"

class Tetromino
{
private:
    int TetrominoSize = 0;
    vector<vector<Block> > block;
    SDL_Point screenPos, mapPos;
    int tetrominoType;
    int rotateDirect;

public:
    Tetromino();
    Tetromino(Tetromino &&) = default;
    Tetromino(const Tetromino &) = default;
    Tetromino(int _x, int _y, vector<vector<bool> > status, Block tetrominoBlock, Block emptyBlock);
    void render(SDL_Renderer *renderer, string type);
    void updateTetromino();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void move(int x, int y);
    void clockwiseRotate();
    void anticlockwiseRotate();
    int getRotateDirect();
    void setAlpha(Uint8 alpha);
    SDL_Point getMapPos() const;
    void setMapPos(int x, int y);
    SDL_Point getScreenPos() const;
    void setScreenPos(int x, int y);
    int getTetrominoType() const;
    int getTetrominoSize() const;
    int getBlockType(int x, int y) const;
    Block getBlock(int x, int y) const;
    Tetromino &operator=(Tetromino &&) = default;
    Tetromino &operator=(const Tetromino &) = default;
    ~Tetromino();
};

#endif // !1
