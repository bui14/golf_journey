#include "darkHole.h"
#include "TextureManager.h"
#include "game.h"


darkHole::darkHole(std::string texturesheet, int x, int y) {
	darkHoleTex = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	srcR.x = 0;
	srcR.y = 0;
	srcR.h = 67;
	srcR.w = 64;
	destR.x = xpos;
	destR.y = ypos;
	destR.h = 67;
	destR.w = 64;

}

darkHole::~darkHole() {
	SDL_DestroyTexture(darkHoleTex);
}

void darkHole::Update()
{
	if (global::balldestR.x + 32 > destR.x && global::balldestR.x + 64 < destR.x + 96 && global::balldestR.y + 32 > destR.y && global::balldestR.y + 64 < destR.y + 96) {
		global::end = true;
	}
}

void darkHole::Render()
{
	SDL_RenderCopy(game::renderer, darkHoleTex, &srcR, &destR);
}
