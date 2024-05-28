#include "hole.h"
#include "TextureManager.h"


hole::hole(std::string texturesheet, int x, int y) {
	holeTex = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	srcR.x = 0;
	srcR.y = 0;
	srcR.h = 19;
	srcR.w = 16;
	destR.x = xpos;
	destR.y = ypos;
	destR.h = 19;
	destR.w = 16;

}

hole::~hole() {
	SDL_DestroyTexture(holeTex);
}

void hole::Update()
{
}

void hole::Render()
{
	SDL_RenderCopy(game::renderer, holeTex, &srcR, &destR);
}
