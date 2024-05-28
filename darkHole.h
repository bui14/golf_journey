#pragma once
#include "game.h"
class darkHole
{
public:
	darkHole(std::string texturesheet, int x, int y);
	~darkHole();

	void Update();
	void Render();

	int xpos;
	int ypos;
	bool end;
	SDL_Rect srcR, destR;
private:

	SDL_Texture* darkHoleTex;
};

