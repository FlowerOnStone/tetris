#ifndef BUTTON__H
#define BUTTON__H
#include "Header.h"
#include "Texture.h"

enum BUTTON_SPRITE
{
    BUTTON_DEFAULT = 0,
    BUTTON_HOVER = 1,
};

class Button
{
private:
    SDL_Point centerPos;
    Texture defaultTexture, hoverTexture;
    int status;
    SDL_Rect buttonRect;

public:
    Button();
    Button(SDL_Point centrePos);
    void setCenterPos(int x, int y);
    SDL_Point getCenterPos();
    void updateButtonRect();
    void loadDefaultTextureFromFile(string path, SDL_Renderer *renderer);
    void loadDefaultTextureFromText(string text, string fontPath, int fontSize, SDL_Color textColor, SDL_Renderer *renderer);
    void loadHoverTextureFromFile(string path, SDL_Renderer *renderer);
    void loadHoverTextureFromText(string text, string fontPath, int fontSize, SDL_Color textColor, SDL_Renderer *renderer);
    int handleEvent(SDL_Event event);
    void render(SDL_Renderer *renderer);
    void free();
    ~Button();
};

#endif // BUTTON__H