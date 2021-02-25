#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"

int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "aw hell naw sdl done fucked up now: " << SDL_GetError() << std::endl;

	if(!IMG_Init(IMG_INIT_PNG)) std::cout << "aw hell naw sdl_image done fucked up now: " << SDL_GetError() << std::endl;

	RenderWindow window("obama gaming",512,512);
	SDL_Texture* playerTexture = window.LoadTexture("res/gfx/player.png");

	std::vector<Entity> entities;
	{
	    int y = -1;
	    int z = 0;
	    for (int i = 0; i < 25; i++) {
	        if (i % 5 == 0) {
	            y++;
	            z = 0;
	        }
	        else z++;
	        entities.push_back(Entity(Vector2((float)z*16,(float)y*16),playerTexture));
	    }
	}

	bool running = true;

	SDL_Event event;

	const float timeStep = .01f;
	float accumulator = .0f;
	float currentTime = utils::hireTimeInSeconds();

	while(running){
		int startTicks = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while(accumulator >= timeStep){
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT )running = false;
			}
			accumulator -= timeStep;

		}

		window.clear();
		for(Entity& e : entities){
			window.render(e);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate()-frameTicks);
	}

	SDL_Quit();

	return 0;
}