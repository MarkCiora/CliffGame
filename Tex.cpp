#include "Tex.h"

#include "helper.h"

#include <iostream>

Tex::tex_path_pair Tex::rock1 = { "Assets/rock1.png", nullptr };
Tex::tex_path_pair Tex::plank_floor2 = { "Assets/plank_floor2.png", nullptr };
Tex::tex_path_pair Tex::guy = { "Assets/guy.png", nullptr };
Tex::tex_path_pair Tex::pink16x16 = { "Assets/pink16x16.png", nullptr};
Tex::tex_path_pair Tex::red16x16 = { "Assets/red16x16.png", nullptr};
Tex::tex_path_pair Tex::green16x16 = { "Assets/green16x16.png", nullptr};

void Tex::InitializeTextureAll() {
	InitializeTexture(rock1);
	InitializeTexture(plank_floor2);
	InitializeTexture(guy);
	InitializeTexture(pink16x16);
	InitializeTexture(red16x16);
	InitializeTexture(green16x16);
}

void Tex::InitializeTexture(tex_path_pair &tpp) {
	if (tpp.t != nullptr)SDL_DestroyTexture(tpp.t);
	auto x = tpp.p.c_str();
	auto surface = IMG_Load(x);
	std::cout << IMG_GetError() << std::endl;
	tpp.t = SDL_CreateTextureFromSurface(helper::MAIN_RENDERER, surface);
	std::cout << IMG_GetError() << std::endl;
	SDL_SetTextureBlendMode(tpp.t, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surface);
}