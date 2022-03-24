#include "Header.h"

class Block
{
private:
    static const int BLOCK_SIZE = 32;
    SDL_Color color;
    int x, y;
    bool active;

public:
    Block();
    Block(int _x, int _y, SDL_Color _color, bool _active);
    void draw(SDL_Renderer *renderer);
    ~Block();
};


