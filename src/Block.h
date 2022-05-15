#ifndef BLOCK__H
#define BLOCK__H

#include "Header.h"
#include "Texture.h"
static const int BLOCK_SIZE = 32;

enum BLOCK_TYPE
{
    BLOCK_TYPE_I,
    BLOCK_TYPE_J,
    BLOCK_TYPE_L,
    BLOCK_TYPE_O,
    BLOCK_TYPE_S,
    BLOCK_TYPE_T,
    BLOCK_TYPE_Z,
    BLOCK_TYPE_WALL,
    BLOCK_TYPE_EMPTY
};

class Block
{
private:
    Texture fullBlock, borderBlock;
    SDL_Rect area;
    int blockType;

public:
    Block();
    Block(int x, int y, int _blockType);
    int getBlockType() const;
    void loadFullBlock(string path, SDL_Renderer *renderer);
    void loadBorderBlock(string path, SDL_Renderer *renderer);
    void setAlpha(Uint8 alpha);
    void changeBlockType(int newBlckType);
    SDL_Rect getArea() const;
    void setScreenPos(int x, int y);
    void render(SDL_Renderer *renderer, string type);
    void free();
    ~Block();
};

SDL_Color createColor(int r, int g, int b, int a);

#endif // BLOCK__H
