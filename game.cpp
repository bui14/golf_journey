#include "game.h"

darkHole* dObj[2];
obstacle* oObj[4];
ball* ballObj;
hole* holeObj;
SDL_Texture* map;
SDL_Rect msrcR, mdestR;
SDL_Rect lsrcR, ldestR;
SDL_Texture* menu;
SDL_Texture* tutorial;
SDL_Texture* winScreen;
SDL_Texture* loseScreen;

game::game()
{}

game::~game()
{
	SDL_DestroyTexture(map);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(tutorial);
}

SDL_Renderer* game::renderer = nullptr;

void game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscrean)
{
	int flag = 0;
	if (fullscrean) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystem initialised..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window) {
			cout << "Window Created !" << endl;
		}
		renderer = SDL_CreateRenderer(window,-1,0);
		if (renderer) {
			cout << "Renderer created !" << endl;
		}
		isRunning = true;
		lose = false;
		win = false;
	}
	
	global::state = 0;
	tutor = false;
	ballObj = new ball("asset/golfball/ball.png",320,420);
	holeObj = new hole("asset/golfball/hole.png", 320, 20);

	for (int i = 0; i < 4; i++) {
		oObj[i] = new obstacle("asset/things/obstacle.png", 160, 20);
	}
	for (int i = 0; i < 2; i++) {
		dObj[i] = new darkHole("asset/things/darkHole.png", 160, 20);
	}
	msrcR = { 0,0,1080,1920 };
	mdestR = { 40,0,560,480 };

	lsrcR = { 0,0,1080,1920 };
	ldestR = { 40,0,560,480 };

	menu = TextureManager::LoadTexture("asset/map/menu.png");
	map = TextureManager::LoadTexture("asset/map/map.png");
	tutorial = TextureManager::LoadTexture("asset/map/intro.png");
	winScreen= TextureManager::LoadTexture("asset/things/winscreen.png");
	loseScreen = TextureManager::LoadTexture("asset/things/losescreen.png");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music* background;
	background = Mix_LoadMUS("music/gamemusicloop.mp3");
	Mix_PlayMusic(background, -1);
}

void game::handleEvent(){
	const Uint8* key_state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&global::e)) {
		switch (global::e.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (global::e.button.button == SDL_BUTTON_LEFT)
			{
				global::mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (global::e.button.button == SDL_BUTTON_LEFT)
			{
				global::mousePressed = false;
			}
			break;
		default:
			break;
		}
	}
	
}
void game::clean(){
	SDL_DestroyWindow(window);

	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	cout << "Game cleaned" << endl;
}

void game::checkStatus()
{
	if (global::balldestR.x + 4 > holeObj->destR.x && global::balldestR.x + 16 < holeObj->destR.x + 20 && global::balldestR.y + 4 > holeObj->destR.y && global::balldestR.y + 16 < holeObj->destR.y + 20&&global::phase==global::phaseMax) {
		if (level < 5) level++;
		else win = true;
		
	}
	if (global::end) {
		lose = true;
	}
	if (level != preLevel) {
		global::nextLevel = true;
	}
	else global::nextLevel = false;
	if (global::phase != prePhase) {
		global::nextPhase = true;
	}
	else global::nextPhase = false;
}

void game::loadScreen() {
	if (global::state == 0 && !tutor) {
		if (global::mousePressed) {
			mouseX = 0;
			mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX >= 192 && mouseX <= 448 && mouseY >= 48 && mouseY <= 137) {
				msrcR = { 0,480,320,480 };
				mdestR = { 160,0,320,480 };
				level = 1;
				preLevel = 0;
				prePhase = 0;
				global::state++;
			}
			if (mouseX >= 192 && mouseX <= 448 && mouseY >= 195 && mouseY <= 284) {
				tutor = true;
			}
			if (mouseX >= 192 && mouseX <= 448 && mouseY >= 342 && mouseY <= 432) {
				isRunning = false;
			}
		}
		
	}
	if (tutor) {
		if (global::mousePressed) {
			mouseX = 0;
			mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
		}
		if (mouseX >= 40 && mouseX <= 186 && mouseY >= 0 && mouseY <= 44) {
			tutor = false;
		}
	}
}

void game::update(){
	ballObj->Update();
	if (level == 1) {
		if (global::nextLevel) {
			global::phaseMax = 1;
			global::phase = 1;
			oObj[0]->destR.x = 160;
			oObj[0]->destR.y = 250;
			preLevel = level;
		}
		if (global::nextPhase) prePhase = global::phase;
		oObj[0]->Update();
	}
	if (level == 2) {
		if (global::nextLevel) {
			global::phaseMax = 1;
			global::phase = 1;
			global::balldestR.x = 320;
			global::balldestR.y = 420;
			oObj[1]->destR.x = 320;
			oObj[1]->destR.y = 150;
			holeObj->destR.x = 455;
			preLevel = level;
		}
		if (global::nextPhase) prePhase = global::phase;
		oObj[0]->Update();
		oObj[1]->Update();
	}
	if (level == 3) {
		if (global::nextLevel) {
			global::phaseMax = 2;
			global::phase = 1;
			global::balldestR.x = 320;
			global::balldestR.y = 420;
			holeObj->destR.x = 412;
			preLevel = level;
		}
		if (global::nextPhase) prePhase = global::phase;
		oObj[1]->destR.y = 180;
		oObj[0]->destR.y = 270;

		dObj[0]->destR.x = 300;
		dObj[0]->destR.y = 100;
		dObj[1]->destR.x = 255;
		dObj[1]->destR.y = 205;
		for (int i = 0; i < 2; i++) {
			oObj[i]->Update();
		}
		if (global::phase == 1) {
			dObj[0]->Update();
		}
		if (global::phase == 2) {
			dObj[0]->Update();
			dObj[1]->Update();
		}
	}
	if (level == 4) {
		if (global::nextLevel) {
			global::phaseMax = 2;
			global::phase = 1;
			global::balldestR.x = 320;
			global::balldestR.y = 420;
			holeObj->destR.x = 177;
			preLevel = level;
		}
		if (global::nextPhase) prePhase = global::phase;
		oObj[1]->destR.y = 100;
		oObj[0]->destR.y = 220;
		oObj[2]->destR.y = 300;
		oObj[3]->destR.y = 350;

		dObj[0]->destR.x = 300;
		dObj[0]-> destR.y = 240;
		dObj[1]->destR.x = 255;
		dObj[1]->destR.y = 125;
		for (int i = 0; i < 4; i++) {
			oObj[i]->Update();
		}
		if (global::phase == 2) {
			for (int i = 0; i < 2; i++) {
				dObj[i]->Update();
			}
		}
		
	}
	if (win) {
		SDL_Delay(900);
		clean();
	}
	if (lose) {
		SDL_Delay(800);
		clean();
	}
	checkStatus();
}

void game::render(){
	
	SDL_RenderClear(renderer);
	if (global::state == 1) {
		TextureManager::draw(map, msrcR, mdestR);
		if (level == 1) {
			oObj[0]->Render();
			holeObj->Render();
			ballObj->Render();
		}
		if (level == 2) {	
			oObj[0]->Render();
			oObj[1]->Render();
			holeObj->Render();
			ballObj->Render();
		}
		if (level == 3) {
			
			if (global::phase == 1) {
				dObj[0]->Render();
			}
			if (global::phase == 2) {
				dObj[0]->Render();
				dObj[1]->Render();
			}
			if (global::phase == global::phaseMax) holeObj->Render();
			for (int i = 0; i < 2; i++) {
				oObj[i]->Render();
			}
			ballObj->Render();
		}
		if (level == 4) {
			for (int i = 0; i < 4; i++) {
				oObj[i]->Render();
			}
			if (global::phase == 2) {
				for (int i = 0; i < 2; i++) {
					dObj[i]->Render();
				}
				for (int i = 0; i < 4; i++) {
					oObj[i]->Render();
				}
			}
			if (global::phase == global::phaseMax) holeObj->Render();
			ballObj->Render();
		}
		if (win) {
			TextureManager::draw(winScreen, lsrcR, ldestR);
		}
		if (lose) {
			TextureManager::draw(loseScreen, lsrcR, ldestR);
		}
	}
	if (tutor) {
		TextureManager::draw(tutorial, msrcR, mdestR);
	}
	if (global::state == 0 && !tutor) {
		TextureManager::draw(menu, msrcR, mdestR);
	}
	
	SDL_RenderPresent(renderer);
}