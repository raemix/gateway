#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Entity.hpp"
#include <vector>

class Player : public Entity{
private:
	std::vector<Entity> x;
public:
	Player(Vector2 pos, SDL_Texture* tex,std::vector<Entity> x);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void animate(int* secs/*hehe*/);
};