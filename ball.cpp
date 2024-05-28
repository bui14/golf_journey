#include "ball.h"
#include "TextureManager.h"
#include "global.h"

ball::ball(std::string texturesheet, int x, int y) {
	ballTex = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	global::ballsrcR = { 0,0,16,16 };
	global::balldestR = { xpos,ypos,16,16 };
}

ball::~ball() {
	SDL_DestroyTexture(ballTex);
}
bool ball::isKeyHeld(SDL_Scancode button) {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[button]) {

		Uint32 startTime = SDL_GetTicks();

		while (state[button] && (SDL_GetTicks() - startTime) < 150) {
			SDL_PumpEvents(); 
		}
		if ((SDL_GetTicks() - startTime) >= 150) {
			return true;
		}
	}
	return false;
}

float ball::timeKeyHeld(SDL_Scancode button) {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[button]) {

		Uint32 startTime = SDL_GetTicks();

		while (state[button]) {
			SDL_PumpEvents();
			state = SDL_GetKeyboardState(NULL);
		}
		Uint32 endTime = SDL_GetTicks();
		return (endTime - startTime <= 350) ? (endTime - startTime) / 100.0f : 350 / 100.0f;
	}
	else return 0.0f;
}


void ball::Update() {
	if (isKeyHeld(SDL_SCANCODE_W)) {
		setLaunchedVel(0, -timeKeyHeld(SDL_SCANCODE_W) * 2);
	}
	else if (isKeyHeld(SDL_SCANCODE_A)) {
		setLaunchedVel(-timeKeyHeld(SDL_SCANCODE_A) * 2, 0);
	}
	else if (isKeyHeld(SDL_SCANCODE_S)) {
		setLaunchedVel(0, timeKeyHeld(SDL_SCANCODE_S) * 2);
	}
	else if (isKeyHeld(SDL_SCANCODE_D)) {
		setLaunchedVel(timeKeyHeld(SDL_SCANCODE_D) * 2, 0);
	}
	else {
		if (global::balldestR.y < 0) {
			if (global::phase == global::phaseMax) {
				global::balldestR.y = 0;
				setLaunchedVel(-velX, -velY);
			}
			else {
				global::balldestR.y = 464;
				global::phase++;
				return;
			}
		}
		if (global::nextLevel || global::nextPhase) {
			setLaunchedVel(0, 0);
		}
		if (global::balldestR.y > 464) {
			global::balldestR.y = 464;
			setLaunchedVel(-velX, -velY);
		}
		if (global::balldestR.x > 464) {
			global::balldestR.x = 464;
			setLaunchedVel(-velX, -velY);
		}
		if (global::balldestR.x < 160) {
			global::balldestR.x = 160;
			setLaunchedVel(-velX, -velY);
		}
		setVelocity(launchedVelX, launchedVelY);

		if (abs(launchedVelX) > 0.1) {
			launchedVelX -= (launchedVelX > 0) ? (float)0.1 : (float)-0.1;
		}
		else if (abs(launchedVelY) > 0.1) {
			launchedVelY -= (launchedVelY > 0) ? (float)0.1 : (float)-0.1;
		}
		else {
			setLaunchedVel(0, 0);
		}
		global::balldestR.x += (int)velX;
		global::balldestR.y += (int)velY;
		
	}
}
void ball::Render() {
	SDL_RenderCopy(game::renderer, ballTex, &global::ballsrcR, &global::balldestR);
}

void ball::setVelocity(float x, float y) {
	velX = x;
	velY = y;
}

void ball::setLaunchedVel(float x, float y)
{
	launchedVelX = x;
	launchedVelY = y;
}