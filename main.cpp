#include <iostream>
#include <SDL2/SDL.h>

#include "GameWindow.h"


//how games are typically set up:
//	initialize -- boot it up, load textures and data
//	event -- player interaction.. clicking, pressing keys etc
//	loop -- the game loop itself.. iterate through movements, physics or whatever
//	render -- render what shows up on the screen
//	cleanup -- deallocate anything loaded

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

	GameWindow gw;
	return gw.OnExecute();
}
