#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Math.hpp"
#include "Entity.hpp"
#include "Player.hpp"

Player::Player(Vector2 pos, SDL_Texture* tex, Mix_Chunk* moveSound, std::vector<Entity> x) : Entity(Vector2(16,16), tex){
	this->x = x;
	this->moveSound = moveSound;
}


// the collision detection system for this game would probably make any self respecting programmer want to burn their eyes out.

//but hey

// it just works


void Player::MoveUp(){
	for(Entity& e : x){
		if((e.getPos().y == pos.y-16) && (e.getPos().x == pos.x)){
			if(e.getCollidable() == false){
				pos.y -= 16;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

void Player::MoveDown(){
	for(Entity& e : x){
		if((e.getPos().y == pos.y+16) && (e.getPos().x == pos.x)){
			if(e.getCollidable() == false){
				pos.y += 16;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

void Player::MoveLeft(){
	for(Entity& e : x){
		if((e.getPos().x == pos.x-16) && (e.getPos().y == pos.y)){
			if(e.getCollidable() == false){
				pos.x -= 16;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

void Player::MoveRight(){
	for(Entity& e : x){
		if((e.getPos().x == pos.x+16) && (e.getPos().y == pos.y)){
			if(e.getCollidable() == false){
				pos.x += 16;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

// int Player::getState(){
// 	return state;
// }

// void Player::setState(int state){
// 	this->state = state;
// }