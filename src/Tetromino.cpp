#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(int x, int y, vector<vector<bool> > status, Block tetrominoBlock, Block emptyBlock) : TetrominoSize(status.size())
{
    rotateDirect = 0;
    screenPos.x = x;
    screenPos.y = y;
    block.resize(TetrominoSize);
    for (int i = 0; i < TetrominoSize; i++)
    {
        block[i].resize(TetrominoSize);
        for (int j = 0; j < TetrominoSize; j++)
        {
            if (status[i][j] == true)
            {
                block[i][j] = tetrominoBlock;
            }
            else
            {
                block[i][j] = emptyBlock;
            }
            block[i][j].setScreenPos(screenPos.x + j * BLOCK_SIZE, screenPos.y + i * BLOCK_SIZE);
        }
    }
    tetrominoType = tetrominoBlock.getBlockType();
    mapPos.x = mapPos.y = 0;
}

void Tetromino::render(SDL_Renderer *renderer, string type)
{
    for (int i = 0; i < TetrominoSize; i++)
    {
        for (int j = 0; j < TetrominoSize; j++)
        {
            if (block[i][j].getBlockType() != BLOCK_TYPE_EMPTY)
            {
                block[i][j].render(renderer, type);
            }
        }
    }
}

void Tetromino::updateTetromino()
{
    for (int i = 0; i < TetrominoSize; i++)
    {
        for (int j = 0; j < TetrominoSize; j++)
        {
            block[i][j].setScreenPos(screenPos.x + j * BLOCK_SIZE, screenPos.y + i * BLOCK_SIZE);
        }
    }
}

void Tetromino::setAlpha(Uint8 alpha)
{
    for (int i = 0; i < TetrominoSize; i++)
    {
        for (int j = 0; j < TetrominoSize; j++)
        {
            block[i][j].setAlpha(alpha);
        }
    }
}

void Tetromino::moveLeft()
{
    screenPos.x -= BLOCK_SIZE;
    mapPos.y--;
    updateTetromino();
}

void Tetromino::moveRight()
{
    screenPos.x += BLOCK_SIZE;
    mapPos.y++;
    updateTetromino();
}

void Tetromino::moveDown()
{
    screenPos.y += BLOCK_SIZE;
    mapPos.x++;
    updateTetromino();
}

void Tetromino::moveUp()
{
    screenPos.y -= BLOCK_SIZE;
    mapPos.x--;
    updateTetromino();
}

void Tetromino::move(int x, int y){
    swap(x, y);
    mapPos.x += x;
    mapPos.y += y;
    screenPos.x += y * BLOCK_SIZE;
    screenPos.y += x * BLOCK_SIZE;
    updateTetromino();
}

void Tetromino::clockwiseRotate()
{
    vector<vector<Block> > tmp = block;
    for (int i = 0; i < TetrominoSize; i++)
    {
        for (int j = 0; j < TetrominoSize; j++)
        {
            block[j][TetrominoSize - i - 1] = tmp[i][j];
        }
    }
    updateTetromino();
    rotateDirect = (rotateDirect + 1) % 4;
}

void Tetromino::anticlockwiseRotate()
{
    vector<vector<Block> > tmp = block;

    for (int i = 0; i < TetrominoSize; i++)
    {
        for (int j = 0; j < TetrominoSize; j++)
        {
            block[TetrominoSize - j - 1][i] = tmp[i][j];
        }
    }
    updateTetromino();
    rotateDirect = (rotateDirect + 3) % 4;
}

int Tetromino::getRotateDirect()
{
    return rotateDirect;
}

SDL_Point Tetromino::getMapPos() const
{
    return mapPos;
}

void Tetromino::setMapPos(int x, int y)
{
    mapPos.x = x;
    mapPos.y = y;
}

SDL_Point Tetromino::getScreenPos() const
{
    return screenPos;
}

void Tetromino::setScreenPos(int x, int y)
{
    screenPos.x = x;
    screenPos.y = y;
    updateTetromino();
}

int Tetromino::getTetrominoType() const
{
    return tetrominoType;
}

int Tetromino::getTetrominoSize() const
{
    return TetrominoSize;
}

int Tetromino::getBlockType(int x, int y) const
{
    assert(x < TetrominoSize && y < TetrominoSize);
    return block[x][y].getBlockType();
}

Block Tetromino::getBlock(int x, int y) const
{
    assert(x < TetrominoSize && y < TetrominoSize);
    return block[x][y];
}

Tetromino::~Tetromino()
{
}
