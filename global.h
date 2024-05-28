#pragma once
#include <SDL.h>
#include "ball.h"

namespace global {
	extern SDL_Event e;
	extern bool mousePressed;
	extern double deltaTime;
	extern bool space;
	extern int state;
	extern SDL_Rect ballsrcR, balldestR;
	extern bool end;
	extern int phaseMax;
	extern int phase;
	extern bool nextLevel;
	extern bool nextPhase;
}