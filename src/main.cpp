#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <cmath>
#include "RenderWindow.hpp"
#include "Audio.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Tilemap.hpp"

void handleInput(SDL_Event* event, Player* character, bool* running){
	while(SDL_PollEvent(event)){
		if(event->type == SDL_QUIT )*running = false;

		else if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && SDL_GetTicks() > 6000){
			if(character->checkMoves()){
				switch(event->key.keysym.sym){
					case SDLK_w:
						character->MoveUp();
						break;
					case SDLK_a:
						character->MoveLeft();
						break;
					case SDLK_s:
						character->MoveDown();
						break;
					case SDLK_d:
						character->MoveRight();
						break;
				}
			}
			switch(event->key.keysym.sym){
				case SDLK_SPACE:
					character->teleport();
					break;
				case SDLK_r:
					character->restart();
					break;
			}
		}
	}
}


int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) std::cout << "SDL could not initialize. Error: " << SDL_GetError() << std::endl;
	if(TTF_Init() < 0) std::cout << "SDL_TTF could not initialize. Error: " << SDL_GetError() << std::endl;
	if(!IMG_Init(IMG_INIT_PNG)) std::cout << "SDL_Image could not initialize. Error: " << SDL_GetError() << std::endl;

	Audio mixer(44100,MIX_DEFAULT_FORMAT,2,248);
	RenderWindow window("gateway",512,512);
	Tilemap tiles("res/dev/tilemap.tmx");
	Mix_Chunk* move = mixer.LoadChunk("res/sfx/move.wav");
	Mix_Chunk* teleport = mixer.LoadChunk("res/sfx/teleport.wav");
	Mix_Chunk* death = mixer.LoadChunk("res/sfx/death.wav");
	TTF_Font* font = TTF_OpenFont("res/ttf/brixel-8x8.ttf", 8);
	SDL_Texture* controlsTexture = window.LoadTexture("res/gfx/keys.png");
	SDL_Texture* playerTexture = window.LoadTexture("res/gfx/player.png");
    Player character(Vector2((float)0,(float)0),playerTexture,move,teleport,death);
    character.setAnimatable(true,14);

	std::vector<Entity> entities = tiles.createEntities(&window, &character);

	character.setEntities(&entities);

	SDL_Event event;
	bool running = true;
	const float timeStep = .01f;
	float accumulator = .0f;
	float currentTime = utils::hireTimeInSeconds();

	while(running){

		int startTicks = SDL_GetTicks();
		int seconds = startTicks / 100;
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;


		currentTime = newTime;
		accumulator += frameTime;
		while(accumulator >= timeStep){
			handleInput(&event, &character, &running);
			accumulator -= timeStep;

		}

		if (SDL_GetTicks() < 3000)
		{
			window.clear();
			window.renderCenter(0, sin(SDL_GetTicks()/200) * 2 - 20, "anactualhuman", font, SDL_Color{ 255, 255, 255 });
			window.renderCenter(0, -sin(SDL_GetTicks()/200) * 2 + 20, "powered by SDL2", font, SDL_Color{ 255, 255, 255 });
			window.display();
		}else if(SDL_GetTicks() < 6000){
			window.clear();
			window.renderCenter(0,sin(SDL_GetTicks()/200) * 2, controlsTexture);
			window.display();
		}else{

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

	TTF_Quit();
	SDL_Quit();

	return 0;
}