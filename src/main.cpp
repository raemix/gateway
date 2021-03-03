#include "../include/Main.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/Audio.hpp"
#include "../include/Utils.hpp"
#include "../include/Entity.hpp"
#include "../include/Tilemap.hpp"
#include "../include/Math.hpp"
#include "../include/Player.hpp"
#include <iostream>


// ttf, sfx, textures etc.
TTF_Font* font;
Mix_Chunk* startUpSound;
Mix_Chunk* move;
Mix_Chunk* teleport;
Mix_Chunk* death;
//Mix_Music* bgm;
SDL_Texture* controlsTexture;
SDL_Texture* bgTexture;
//

RenderWindow window;
Audio mixer;
Tilemap tiles;

std::vector<Entity> entities;
Vector2 portal;
Vector2 bg1Pos = Vector2(0,0);
Vector2 bg2Pos = Vector2(-128,0);

// timestep stuff
const float timeStep = .01f;
float accumulator = .0f;
float currentTime = utils::hireTimeInSeconds();
//

// input
SDL_Event event;
//

bool running = true;

bool init(){

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) std::cout << "SDL could not initialize. Error: " << SDL_GetError() << std::endl;

	if(TTF_Init() < 0) std::cout << "SDL_TTF could not initialize. Error: " << SDL_GetError() << std::endl;

	if(!IMG_Init(IMG_INIT_PNG)) std::cout << "SDL_Image could not initialize. Error: " << SDL_GetError() << std::endl;

	window.start("game",512,512);
	mixer.start(44100,MIX_DEFAULT_FORMAT,2,1240);

	font = TTF_OpenFont("res/ttf/brixel-8x8.ttf", 8);
	move = mixer.LoadChunk("res/sfx/move.wav");
	teleport = mixer.LoadChunk("res/sfx/teleport.wav");
	death = mixer.LoadChunk("res/sfx/death.wav");
	//bgm = mixer.LoadMusic("res/sfx/???.mp3");
	controlsTexture = window.LoadTexture("res/gfx/keys.png");
	bgTexture = window.LoadTexture("res/gfx/bg.png");
	character.setAnimatable(true,14);

	return true;
}

bool initialize = init();

Player character(Vector2((float)16,(float)16),window.LoadTexture("res/gfx/player.png"),move,teleport,death);

void loadLevel(const char* level){
	entities.clear();
	tiles.loadTilemap(level);
	std::pair<std::vector<Entity>,Vector2> createEnts = tiles.createEntities();

	entities = createEnts.first;
	portal = createEnts.second;

	character.setEntities(&entities);
	character.setPortalPosition(&portal);
}


void handleInput(SDL_Event* event, bool* running){
	while(SDL_PollEvent(event)){
		if(event->type == SDL_QUIT )*running = false;

		else if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && SDL_GetTicks() > 7500){
			if(character.checkMoves()){
				switch(event->key.keysym.sym){
					case SDLK_w:
						character.newPosition(Vector2(character.getPos().x,character.getPos().y-16));
						break;
					case SDLK_a:
						character.newPosition(Vector2(character.getPos().x-16,character.getPos().y));
						break;
					case SDLK_s:
						character.newPosition(Vector2(character.getPos().x,character.getPos().y+16));
						break;
					case SDLK_d:
						character.newPosition(Vector2(character.getPos().x+16,character.getPos().y));
						break;
				}
			}
			switch(event->key.keysym.sym){
				case SDLK_SPACE:
					character.teleport();
					break;
				case SDLK_r:
					character.restart();
					break;
			}
		}
	}
}

void loop(){
	int startTicks = SDL_GetTicks();
	int seconds = startTicks / 100;
	float newTime = utils::hireTimeInSeconds();
	float frameTime = newTime - currentTime;

	currentTime = newTime;
	accumulator += frameTime;

	while(accumulator >= timeStep){
		handleInput(&event, &running);
		accumulator -= timeStep;

	}

	if (SDL_GetTicks() < 3000)
	{
		window.clear();
		window.renderCenter(0, sin(SDL_GetTicks()/200) * 3 - 20, "anactualhuman", font, SDL_Color{ 255, 255, 255 });
		window.renderCenter(0, -sin(SDL_GetTicks()/200) * 3 + 20, "powered by SDL2", font, SDL_Color{ 255, 255, 255 });
		window.display();
	}
	else if(SDL_GetTicks() < 7500){
		window.clear();
		window.renderCenter(0,sin(SDL_GetTicks()/200) * 2, controlsTexture);
		window.display();
	}else
	{

		character.animate(seconds);
		window.clear();
		bg1Pos.x += 48 * timeStep;
		bg2Pos.x += 48 * timeStep;
		if(bg1Pos.x >= 128){
			bg1Pos.x = -128;
		}
		if(bg2Pos.x >= 128){
			bg2Pos.x = -128;
		}
		window.renderCenter(bg1Pos.x,bg1Pos.y,bgTexture);
		window.renderCenter(bg2Pos.x,bg2Pos.y,bgTexture);
		for(Entity& e : entities){
			if(e.getAnimatable()){
				e.animate(seconds);
			}
			window.render(e);
		}
		window.render(character);
		window.renderCenter(0, -56, character.getMoves(), font, SDL_Color{ 255, 255, 255 });
		window.display();
	}

	int frameTicks = SDL_GetTicks() - startTicks;

	if(frameTicks < 1000 / window.getRefreshRate())
		SDL_Delay(1000 / window.getRefreshRate()-frameTicks);

}

int main(int argc, char* args[]){
	//Mix_PlayMusic(bgm,-1);

	loadLevel("res/dev/tilemap1.tmx");

	while(running){
		loop();
	}

	TTF_Quit();
	SDL_Quit();

	return 0;
}
