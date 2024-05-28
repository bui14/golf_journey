#include "TextureManager.h"
#include "game.h"

SDL_Texture* TextureManager::LoadTexture(std::string texture) {
	SDL_Surface* tempSurface = IMG_Load(texture.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(game::renderer, tex, &src, &dest);
}
