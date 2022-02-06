#include "VisualObject.h"

std::vector<VisualObject*> VisualObject::dot_list;
bool VisualObject::showdots = true;

void VisualObject::AddDotPink(const Vec2& vec){
    auto ptr = new VisualObject(dot_pink, vec);
    dot_list.push_back(ptr);

}void VisualObject::AddDotRed(const Vec2& vec){
    auto ptr = new VisualObject(dot_red, vec);
    dot_list.push_back(ptr);
}

void VisualObject::ResetDot(){
    for(auto &it : dot_list) delete it;
    dot_list.clear();
}

VisualObject::VisualObject(VOType t = dot_pink, Vec2 p = Vec2()){
    pos = p;
    type = t;
    width = 12;
    height = 12;
    src.x = 0;
    src.y = 0;
    src.w = 16;
    src.h = 16;
    if (type == dot_pink) texture = Tex::pink16x16.t;
    else texture = Tex::red16x16.t;
}

void VisualObject::RenderAll(){
    
    if (showdots) for(auto &it : dot_list){
        it->Render();
    }
}

void VisualObject::Render(){
	dest.w = width;
	dest.h = height;
	dest.x = pos.x * helper::world_ratio - (dest.w >> 1);
	dest.y = pos.y * helper::world_ratio - (dest.h >> 1);
	SDL_RenderCopy(helper::MAIN_RENDERER, texture, &src, &dest);
}