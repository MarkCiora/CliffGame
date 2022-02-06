#include "GameWindow.h"


#include "helper.h"
#include "Tex.h"
#include "PhysicsObject.h"
#include "VisualObject.h"
#include "VisualLine.h"

#include <string>
#include <chrono>
#include <iostream>
#include <cmath>

#include <unistd.h>

using std::string;


//ON LOOP
void GameWindow::OnLoop() {
	VisualObject::ResetDot();
	auto dt_float = (float)dt;
	game->GameLoop(dt_float);
}

//EVENT
void GameWindow::EventHandler(SDL_Event* Event) {
	if (Event->type == SDL_KEYDOWN) {
		if (Event->key.keysym.sym == SDLK_ESCAPE) {
			running = false;
			return;
		}
		if(Event->key.keysym.sym == SDLK_F2){
			SDL_SetWindowFullscreen(MAIN_WINDOW, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		if(Event->key.keysym.sym == SDLK_F1){
			VisualObject::showdots = !VisualObject::showdots;
		}
		if(Event->key.keysym.sym == SDLK_r){
			game->ResetGame();
		}
	}

	if (Event->type == SDL_MOUSEBUTTONDOWN) {
		if (Event->button.button == SDL_BUTTON_RIGHT) {
			Vec2 dest;
			dest.x = Event->button.x;
			dest.y = Event->button.y;
		}
		if (Event->button.button == SDL_BUTTON_LEFT) {
			Vec2 dest;
			dest.x = Event->button.x;
			dest.y = Event->button.y;
		}
	}
}

void GameWindow::ProcessContinuousEvents() {
	SDL_PumpEvents();
	auto keystate = SDL_GetKeyboardState(NULL);
	if(keystate[SDL_SCANCODE_E]){
		game->player->angle = game->player->angle + 100.f * dt;
	}
	if(keystate[SDL_SCANCODE_Q]){
		game->player->angle = game->player->angle - 100.f * dt;
	}
	if(keystate[SDL_SCANCODE_W]){
		game->player->pos = game->player->pos + Vec2(0,-2.f)* dt;
	}
	if(keystate[SDL_SCANCODE_A]){
		game->player->pos = game->player->pos + Vec2(-2.f, 0)* dt;
	}
	if(keystate[SDL_SCANCODE_S]){
		game->player->pos = game->player->pos + Vec2(0,2.f)* dt;
	}
	if(keystate[SDL_SCANCODE_D]){
		game->player->pos = game->player->pos + Vec2(2.f,0)* dt;
	}
}

//execute
int GameWindow::OnExecute() {
	program_start_time = std::chrono::system_clock::now();
	if (!OnInit()) return -1;
	SDL_Event *Event = new SDL_Event();
	start_time = std::chrono::system_clock::now();
	while (true) {
		ProcessContinuousEvents();
		while (SDL_PollEvent(Event)) EventHandler(Event);
		if (!running) break;
		OnLoop();
		OnRender();
		//maybe start the next loop before wait
		//and then only render it once the last frame is stopped
		WaitNextFrame();
	}
	delete Event;
	OnCleanup();
	return 0;
}

void GameWindow::WaitNextFrame() {
	end_time = std::chrono::system_clock::now();
	std::chrono::duration<double> x = end_time - start_time;
	//std::cout << x.count() << std::endl;

	auto elapsed_seconds = end_time - start_time;
	dt = elapsed_seconds.count() * 1e-9;

	start_time = std::chrono::system_clock::now();
}

//CLEANUP
void GameWindow::OnCleanup() {
	delete game;
	//free all textures

	SDL_DestroyRenderer(helper::MAIN_RENDERER);
	SDL_DestroyWindow(MAIN_WINDOW);

	IMG_Quit();
	SDL_Quit();
}

//INIT
bool GameWindow::OnInit() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
	(IMG_Init(IMG_INIT_PNG));

	MAIN_WINDOW = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, helper::SCREEN_WIDTH, helper::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (MAIN_WINDOW == nullptr) return false;

	helper::MAIN_RENDERER = SDL_CreateRenderer(MAIN_WINDOW, -1, SDL_RENDERER_ACCELERATED);

	Tex::InitializeTextureAll();

	game = new Game();

	return true;
}

//RENDER
void GameWindow::OnRender() {
	SDL_RenderClear(helper::MAIN_RENDERER);

	PhysicsObject::RenderAll();
	VisualObject::RenderAll();
	VisualLine::RenderAll();
	
    SDL_SetRenderDrawColor(helper::MAIN_RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderPresent(helper::MAIN_RENDERER);
}
