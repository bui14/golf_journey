#ifndef game_h
#define game_h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global.h"
#include "ball.h"
#include "TextureManager.h"
#include "darkHole.h"
#include "hole.h"
#include "obstacle.h"
#include <SDL_mixer.h>

using namespace std;
class game
{
public:

	game();
	~game();

	void init(const char* title,int xpos,int ypos,int width,int height,bool fullscrean);
	void handleEvent();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };
	static SDL_Renderer* renderer;
	void checkStatus();
	void loadScreen();

private:
	int mouseX, mouseY;
	SDL_Window* window;
	bool isRunning;
	bool tutor;
	int level;
	int preLevel;
	int prePhase;
	bool lose;
	bool win;
};

#endif /* game_h */