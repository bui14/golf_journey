#include "game.h"
#include "music.h"

game* GAME = nullptr;

int main(int argc, char* argv[]) {
	const int FPS = 165;
	const int frameDelay = 1000 / FPS;

	GAME = new game();

	Uint32 frameStart;
	int frameTime;

	GAME->init("golf's journey",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,false);
	double lowLimit = 0.0167;
	double highLimit = 0.1;


	while (GAME->running()) {
		frameStart = SDL_GetTicks();

		GAME->handleEvent();
		GAME->loadScreen();
		GAME->update();
		GAME->render();

		frameTime = SDL_GetTicks() - frameStart;

		global::deltaTime = frameTime / 1000.0;
		if (global::deltaTime > highLimit) {
			global::deltaTime= highLimit;
		}
		else if (global::deltaTime <lowLimit)
			global::deltaTime = lowLimit;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	GAME->clean();

	return 0;
}