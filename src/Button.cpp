#include "Button.h"

Button::Button()
{
}

Button::Button(SDL_Point centerPos)
{
    this->centerPos = centerPos;
}

void Button::setCenterPos(int x, int y)
{
    centerPos.x = x;
    centerPos.y = y;
    updateButtonRect();
}

SDL_Point Button::getCenterPos()
{
    return centerPos;
}

void Button::updateButtonRect()
{
    buttonRect.w = defaultTexture.getWidth();
    buttonRect.h = defaultTexture.getHeight();
    buttonRect.x = centerPos.x - buttonRect.w / 2;
    buttonRect.y = centerPos.y - buttonRect.h / 2;
}

void Button::loadDefaultTextureFromFile(string filePath, SDL_Renderer *renderer)
{
    defaultTexture.loadFromFile(filePath, renderer);
    updateButtonRect();
}

void Button::loadDefaultTextureFromText(string text, string fontPath, int fontSize, SDL_Color textColor, SDL_Renderer *renderer)
{
    defaultTexture.loadFromRenderedText(text, fontPath, fontSize, textColor, renderer);
    updateButtonRect();
}

void Button::loadHoverTextureFromFile(string filePath, SDL_Renderer *renderer)
{
    hoverTexture.loadFromFile(filePath, renderer);
}

void Button::loadHoverTextureFromText(string text, string fontPath, int fontSize, SDL_Color textColor, SDL_Renderer *renderer)
{
    hoverTexture.loadFromRenderedText(text, fontPath, fontSize, textColor, renderer);
}

int Button::handleEvent(SDL_Event event)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < buttonRect.x || x >= buttonRect.x + buttonRect.w || y < buttonRect.y || y >= buttonRect.y + buttonRect.h)
        {
            status = BUTTON_DEFAULT;
            return 0;
        }
        status = BUTTON_HOVER;
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            return 1;
        }
    }
    return 0;
}

void Button::render(SDL_Renderer *renderer)
{
    if (status == BUTTON_DEFAULT)
    {
        defaultTexture.render(&buttonRect, renderer);
    }
    else
    {
        hoverTexture.render(&buttonRect, renderer);
    }
}

void Button::free()
{
    defaultTexture.free();
    hoverTexture.free();
}

Button::~Button()
{
}
