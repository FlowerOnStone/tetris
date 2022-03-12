#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class Block
{
private:
    static const int BLOCK_SIZE =250;
    SDL_Color color;
    int x, y;

public:
    Block();
    Block(int x, int y, SDL_Color color);
    void draw(SDL_Renderer *renderer);
    ~Block();
};

Block::Block()
{
}

Block::Block(int x, int y, SDL_Color color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}

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
