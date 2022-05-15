#include "Block.h"

Block::Block()
{
}

Block::Block(int x, int y, int _blockType) : blockType(_blockType)
{
    area.x = x;
    area.y = y;
    area.h = area.w = BLOCK_SIZE;
}

void Block::loadFullBlock(string path, SDL_Renderer *renderer)
{
    fullBlock.loadFromFile(path, renderer);
}

void Block::loadBorderBlock(string path, SDL_Renderer *renderer)
{
    borderBlock.loadFromFile(path, renderer);
}

void Block::render(SDL_Renderer *renderer, string type)
{
    if (type == "SOLID")
    {
        fullBlock.render(&area, renderer);
    }
    else
    {
        borderBlock.render(&area, renderer);
    }
}

int Block::getBlockType() const
{
    return blockType;
}

void Block::changeBlockType(int newBlockType)
{
    blockType = newBlockType;
}

SDL_Rect Block::getArea() const
{
    return area;
}

void Block::setScreenPos(int x, int y)
{
    area.x = x;
    area.y = y;
}

void Block::free()
{
    fullBlock.free();
    borderBlock.free();
}

void Block::setAlpha(Uint8 alpha)
{
    fullBlock.setAlpha(alpha);
    borderBlock.setAlpha(alpha);
}

Block::~Block()
{
}

SDL_Color createColor(int r, int g, int b, int a)
{
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}