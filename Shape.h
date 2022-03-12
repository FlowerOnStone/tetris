#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class Shape
{
private:
    SDL_Color color;
    int matrix[4][4];
    int x, y;

public:
    Shape();
    Shape(Shape &&) = default;
    Shape(const Shape &) = default;
    Shape &operator=(Shape &&) = default;
    Shape &operator=(const Shape &) = default;
    ~Shape();

};

Shape::Shape()
{
}

Shape::~Shape()
{
}