#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Math.hpp"
#include "Entity.hpp"
#include <vector>

class Player : public Entity{
private:
	std::vector<Entity> x;
	Mix_Chunk* moveSound;
public:
	Player(Vector2 pos, SDL_Texture* tex,Mix_Chunk* moveSound, std::vector<Entity> x);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};