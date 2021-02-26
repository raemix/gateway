#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Tilemap.hpp"


void handleInput(SDL_Event* event, Player* character, bool* running){
	while(SDL_PollEvent(event)){
		if(event->type == SDL_QUIT )*running = false;

		else if (event->type == SDL_KEYDOWN && event->key.repeat == 0){
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
	}
}


int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "aw hell naw sdl done fucked up now: " << SDL_GetError() << std::endl;

	if(!IMG_Init(IMG_INIT_PNG)) std::cout << "aw hell naw sdl_image done fucked up now: " << SDL_GetError() << std::endl;

	RenderWindow window("gateway",512,512);
	Tilemap tiles("res/dev/tilemap.tmx");

	std::vector<Entity> entities = tiles.createEntities(&window);

	SDL_Texture* playerTexture = window.LoadTexture("res/gfx/player.png");
    Player character(Vector2((float)0,(float)0),playerTexture,entities);

	bool running = true;

	SDL_Event event;

	const float timeStep = .01f;
	float accumulator = .0f;
	float currentTime = utils::hireTimeInSeconds();

	while(running){
		int startTicks = SDL_GetTicks();
		int seconds = startTicks / 100;
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		character.animate(&seconds);

		currentTime = newTime;

		accumulator += frameTime;

		while(accumulator >= timeStep){
			handleInput(&event, &character, &running);
			accumulator -= timeStep;

		}

		window.clear();

		for(Entity& e : entities){
			window.render(e);
		}
		window.render(character);

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate()-frameTicks);
	}

	SDL_Quit();

	return 0;
}