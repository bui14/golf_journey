#pragma once
#include "game.h"

class ball
{
public:
	ball(std::string texturesheet, int x, int y);
	~ball();

	void Update();
	void Render();

	int xpos;
	int ypos;

	void setVelocity(float x, float y);
	void setLaunchedVel(float x, float y);
	bool isKeyHeld(SDL_Scancode button);
	const Uint8* key_state = SDL_GetKeyboardState(NULL);
	float timeKeyHeld(SDL_Scancode button);
	
private:
	SDL_Texture* ballTex;
	bool canMove = true;
	float velX;
	float velY;
	float launchedVelX;
	float launchedVelY;
};