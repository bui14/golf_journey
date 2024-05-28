#pragma once
#include "game.h"
class hole
{
public:
	hole(std::string texturesheet, int x, int y);
	~hole();

	void Update();
	void Render();

	int xpos;
	int ypos;
	SDL_Rect srcR, destR;
private:
	
	SDL_Texture *holeTex;
};

