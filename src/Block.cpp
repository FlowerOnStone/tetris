#include "Block.h"

Block::Block()
{
}

Block::Block(int _x, int _y, SDL_Color _color, bool _active) : x(_x), y(_y), color(_color), active(_active) {}

void Block::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = BLOCK_SIZE;
    rect.w = BLOCK_SIZE;
    SDL_RenderFillRect(renderer, &rect);
}

Block::~Block()
{
}