#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Entity.hpp"
#include "Player.hpp"

Player::Player(Vector2 pos, SDL_Texture* tex, std::vector<Entity> x) : Entity(pos, tex){
	this->x = x;
}


// the collision detection system for this game would probably make any self respecting programmer want to burn their eyes out.

//but hey

// it just works

void Player::MoveUp(){
	for(Entity& e : x){
		if((e.getPos().y == pos.y-16) && (e.getPos().x == pos.x)){
			if(e.getCollidable() == false){
				pos.y -= 16;
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
				break;
			}else{
				break;
			}
		}
	}
	// if(pos.y+16 != 32){
	// 	pos.y += 16;
	// }
	// for(Entity& e : x){
	// 	if(e.getPos().y != (pos.y+16) && !e.getCollidable()){
	// 		pos.y += 16;
	// 		break;
	// 	}
	// }
}

void Player::MoveLeft(){
	for(Entity& e : x){
		if((e.getPos().x == pos.x-16) && (e.getPos().y == pos.y)){
			if(e.getCollidable() == false){
				pos.x -= 16;
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
				break;
			}else{
				break;
			}
		}
	}
}