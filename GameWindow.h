#pragma once

#include "Vec2.h"
#include "Matrix2D.h"
#include "Game.h"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include <chrono>

using std::string;

class GameWindow
{
public:
	int OnExecute();
	bool OnInit();
	void EventHandler(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnCleanup();
	void WaitNextFrame();
	void ProcessContinuousEvents();

private:
	bool running = true;
	double dt = 0;
	SDL_Window* MAIN_WINDOW = nullptr;
	std::chrono::system_clock::time_point program_start_time,start_time,end_time;
	Game* game;
};

