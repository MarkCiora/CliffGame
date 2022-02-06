#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace helper
{
	const int SCREEN_WIDTH = 1400, SCREEN_HEIGHT = 800;
	const float SCREEN_WIDTHF = 1400., SCREEN_HEIGHTF = 800.;
	extern SDL_Renderer* MAIN_RENDERER;
	extern int world_ratio;
};
