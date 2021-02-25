#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"

class Entity{
public:
	Entity(Vector2 pos, SDL_Texture* tex);
	Vector2& getPos();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	bool& getCollidable();
	void setCollidable(bool x);
protected:
	Vector2 pos;
	bool collidable = false;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};