#pragma once
#include "game.h"
class obstacle
{
public:
	obstacle(std::string texturesheet, int x, int y);
	~obstacle();

	void Update();
	void Render();

	int xpos;
	int ypos;
	bool end;
	SDL_Rect srcR, destR;
private:

	SDL_Texture* obstacleTex;
};

