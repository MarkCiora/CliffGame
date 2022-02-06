#pragma once

#include "Vec2.h"

#include <vector>

class VisualLine{
public:
    static std::vector<VisualLine*> list;
    static void RenderAll();
    static void ClearList();
    static void AddLine(const Vec2& v1, const Vec2& v2);
    void Render();

    Vec2 a, b;

    VisualLine(const Vec2& v1, const Vec2& v2);
};