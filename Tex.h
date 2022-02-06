#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

using std::string;

namespace Tex {
	struct tex_path_pair {
		string p;
		SDL_Texture* t;
	};

	extern tex_path_pair
	rock1,
	plank_floor2,
	guy,
	pink16x16,
	red16x16,
	green16x16;

	void InitializeTextureAll();
	void InitializeTexture(tex_path_pair&);
}