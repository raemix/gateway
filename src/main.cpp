#include "Main.hpp"
#include "RenderWindow.hpp"
#include "Audio.hpp"
#include "Utils.hpp"
#include "Entity.hpp"
#include "Tilemap.hpp"
#include "Math.hpp"
#include "Player.hpp"
#include <iostream>


// ttf, sfx, textures etc.
TTF_Font* font;
Mix_Chunk* startUpSound;
Mix_Chunk* move;
Mix_Chunk* teleport;
Mix_Chunk* death;
SDL_Texture* controlsTexture;
//

RenderWindow window;
Audio mixer;
Tilemap tiles;

std::vector<Entity> entities;
Vector2 portal;

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
	mixer.start(44100,MIX_DEFAULT_FORMAT,2,248);

	font = TTF_OpenFont("res/ttf/brixel-8x8.ttf", 8);
	startUpSound = mixer.LoadChunk("res/sfx/startup.wav");
	move = mixer.LoadChunk("res/sfx/move.wav");
	teleport = mixer.LoadChunk("res/sfx/teleport.wav");
	death = mixer.LoadChunk("res/sfx/death.wav");
	controlsTexture = window.LoadTexture("res/gfx/keys.png");
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
		
		else if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && SDL_GetTicks() > 4000){
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

	if (SDL_GetTicks() < 2000)
	{
		window.clear();
		window.renderCenter(0, sin(SDL_GetTicks()/200) * 3 - 20, "anactualhuman", font, SDL_Color{ 255, 255, 255 });
		window.renderCenter(0, -sin(SDL_GetTicks()/200) * 3 + 20, "powered by SDL2", font, SDL_Color{ 255, 255, 255 });
		window.display();
	}
	else if(SDL_GetTicks() < 4000){
		window.clear();
		window.renderCenter(0,sin(SDL_GetTicks()/200) * 2, controlsTexture);
		window.display();
	}else
	{
		character.animate(seconds);
		window.clear();
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
	Mix_PlayChannel(-1,startUpSound,0);

	loadLevel("res/dev/tilemap1.tmx");

	while(running){
		loop();
	}

	TTF_Quit();
	SDL_Quit();

	return 0;
}