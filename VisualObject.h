#pragma once

#include "Vec2.h"
#include "Tex.h"
#include "helper.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

enum VOType{
    dot_pink, dot_red
};

class VisualObject{
public:
    static std::vector<VisualObject*> dot_list;
    static void AddDotPink(const Vec2&);
    static void AddDotRed(const Vec2&);
    static void RenderAll();
    static void ResetDot();

    VOType type;
    Vec2 pos;
    float width, height;
    SDL_Rect src, dest;
    SDL_Texture *texture;

    static bool showdots;
    
    VisualObject(VOType, Vec2);
    void Render();
};