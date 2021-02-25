#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO) > 0) std::cout << "aw hell naw sdl done fucked up now: " << SDL_GetError() << std::endl;

	if(!IMG_Init(IMG_INIT_PNG)) std::cout << "aw hell naw sdl_image done fucked up now: " << SDL_GetError() << std::endl;

	RenderWindow window("gateway",512,512);
	std::string map;
	{
		//SDL_Texture* playerTexture = window.LoadTexture("res/gfx/player.png");
	    rapidxml::file<> xmlFile("tilemap.tmx");
	    // dump document on heap
	    rapidxml::xml_document<>* doc = new rapidxml::xml_document<>();
	    doc->parse<0>(xmlFile.data());
	    rapidxml::xml_node<>* node = doc->first_node("map")->first_node("layer")->first_node("data");

	    std::stringstream ss;
	    ss << *node;


	    for (int i = 0; i < ss.str().length(); i++) {
	        if (std::isdigit(ss.str()[i])) map += ss.str()[i];
	    }

	    delete doc;
	}

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
            char x[] = "res/gfx/tile .png";
            x[12] = map[i]-1;
            SDL_Texture* texture = window.LoadTexture(x);
            entities.push_back(Entity(Vector2((float)z*16,(float)y*16),texture));
            if(map[i] == '2'){
            	entities[i].setCollidable(true);
            }
        }
    }
	SDL_Texture* playerTexture = window.LoadTexture("res/gfx/player.png");
    Player character(Vector2((float)0,(float)0),playerTexture,entities);

	//Tilemap tiles("tilemap.tmx",&window);

	// std::vector<Entity> entities;
	// {
	//     int y = -1;
	//     int z = 0;
	//     for (int i = 0; i < 25; i++) {
	//         if (i % 5 == 0) {
	//             y++;
	//             z = 0;
	//         }
	//         else z++;
	//         entities.push_back(Entity(Vector2((float)z*16,(float)y*16),playerTexture));
	//     }
	// }

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
				else if (event.type == SDL_KEYUP){
					switch(event.key.keysym.sym){
						case SDLK_w:
							character.MoveUp();
							break;
						case SDLK_a:
							character.MoveLeft();
							break;
						case SDLK_s:
							character.MoveDown();
							break;
						case SDLK_d:
							character.MoveRight();
							break;
					}
				}
			}
			accumulator -= timeStep;

		}

		window.clear();
		for(Entity& e : entities){
			window.render(e);
			window.render(character);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate()-frameTicks);
	}

	SDL_Quit();

	return 0;
}