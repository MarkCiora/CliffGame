#include "VisualLine.h"

#include "helper.h"

std::vector<VisualLine*> VisualLine::list;

void VisualLine::RenderAll(){
    for (auto &it : list) it->Render();
    ClearList();
}

void VisualLine::ClearList(){
    for (auto &it : list) delete it;
    list.clear();
}

void VisualLine::AddLine(const Vec2& v1, const Vec2& v2){
    auto ptr = new VisualLine(v1,v2);
    list.push_back(ptr);
}

void VisualLine::Render(){
    SDL_SetRenderDrawColor(helper::MAIN_RENDERER, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(helper::MAIN_RENDERER, a.x, a.y, b.x, b.y);
}

VisualLine::VisualLine(const Vec2& v1, const Vec2& v2){
    a = v1 * helper::world_ratio;
    b = v2 * helper::world_ratio;
}