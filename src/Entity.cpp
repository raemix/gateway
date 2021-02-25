#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2 pos, SDL_Texture* tex):pos(pos),tex(tex){
	currentFrame = {0,0,16,16};
}

Vector2& Entity::getPos(){
	return pos;
}

SDL_Texture* Entity::getTex(){
	return tex;
}

SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}

bool& Entity::getCollidable(){
	return collidable;
}

void Entity::setCollidable(bool x){
	collidable = x;
}