#include "obstacle.h"
#include "TextureManager.h"
#include "game.h"


obstacle::obstacle(std::string texturesheet, int x, int y) {
	obstacleTex = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	srcR.x = 0;
	srcR.y = 0;
	srcR.h = 35;
	srcR.w = 32;
	destR.x = xpos;
	destR.y = ypos;
	destR.h = 35;
	destR.w = 32;

}

obstacle::~obstacle() {
	SDL_DestroyTexture(obstacleTex);
}

void obstacle::Update()
{
	destR.x += 2;
	if (destR.x >= 450) destR.x = 160;
	if (global::balldestR.x + 16 > destR.x && global::balldestR.x + 32 < destR.x + 48 && global::balldestR.y + 16 > destR.y && global::balldestR.y + 32 < destR.y + 48) {
		global::end = true;
	}
}

void obstacle::Render()
{
	SDL_RenderCopy(game::renderer, obstacleTex, &srcR, &destR);
}
