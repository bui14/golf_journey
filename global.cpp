#include "global.h"

SDL_Event global::e;
bool global::mousePressed; //bam chuot
double global::deltaTime;  //frame rate independent
bool global::space;
int global::state;
SDL_Rect global::ballsrcR, global::balldestR;
bool global::end = false;
int global::phaseMax;
int global::phase;
bool global::nextLevel;
bool global::nextPhase;