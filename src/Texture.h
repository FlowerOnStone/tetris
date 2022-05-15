#ifndef TEXTURE__H
#define TEXTURE__H

#include "Header.h"

// Texture wrapper class
class Texture
{
public:
    // Initializes variables
    Texture();
    // Deallocates memory
    ~Texture();
    // Loads image at specified path
    bool loadFromFile(string path, SDL_Renderer *renderer);
    // Creates image from font string
    bool loadFromRenderedText(string textureText, string fontPath, int fontSize, SDL_Color textColor, SDL_Renderer *renderer);
    // Deallocates texture
    void free();
    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    // Set blending
    void setBlendMode(SDL_BlendMode blending);
    // Set alpha modulation
    void setAlpha(Uint8 alpha);
    // Renders texture at given point
    void render(SDL_Rect * renderArea, SDL_Renderer *renderer, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // Gets image dimensions
    int getWidth();
    int getHeight();
private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

#endif // TEXTURE__H