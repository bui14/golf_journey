#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(std::string filename);
	static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};


#endif //TEXTUREMANAGER_H

