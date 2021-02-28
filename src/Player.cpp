#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Math.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include <string>

Player::Player(Vector2 pos, SDL_Texture* tex, Mix_Chunk* moveSound,Mix_Chunk* teleportSound, Mix_Chunk* deathSound) : Entity(Vector2(16,16), tex){
	this->moveSound = moveSound;
	this->teleportSound = teleportSound;
	this->deathSound = deathSound;
	moves = moveCounts[currentLevel];
}


// the collision detection system for this game would probably make any self respecting programmer want to burn their eyes out.

//but hey

// it just works


void Player::MoveUp(){
	for(Entity& e : entities){
		if((e.getPos().y == pos.y-16) && (e.getPos().x == pos.x)){
			if(e.getCollidable() == false){
				pos.y -= 16;
				moves -= 1;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

void Player::MoveDown(){
	for(Entity& e : entities){
		if((e.getPos().y == pos.y+16) && (e.getPos().x == pos.x)){
			if(e.getCollidable() == false){
				pos.y += 16;
				moves -= 1;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

void Player::MoveLeft(){
	for(Entity& e : entities){
		if((e.getPos().x == pos.x-16) && (e.getPos().y == pos.y)){
			if(e.getCollidable() == false){
				pos.x -= 16;
				moves -= 1;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

void Player::MoveRight(){
	for(Entity& e : entities){
		if((e.getPos().x == pos.x+16) && (e.getPos().y == pos.y)){
			if(e.getCollidable() == false){
				pos.x += 16;
				moves -= 1;
				Mix_PlayChannel(-1,moveSound,0);
				break;
			}else{
				break;
			}
		}
	}
}

const char* Player::getMoves(){
	std::string m = std::to_string(moves);
	m = "Moves: " + m;
	return m.c_str();
}

bool Player::checkMoves(){
	if(moves > 0){
		return true;
	}else{
		return false;
	}
}

void Player::setEntities(std::vector<Entity>* entities){
	this->entities = *entities;
}

void Player::portalPushBack(Vector2 position){
	portalPositions.push_back(position);
}

void Player::teleport(){
	if(currentPortal < portalPositions.size()){
		pos = portalPositions[currentPortal];
		currentPortal++;
		Mix_PlayChannel(-1,teleportSound,0);
	}
}

void Player::restart(){
	if(currentPortal > 0){
		currentPortal--;
	}
	moves = moveCounts[currentLevel];
	pos = Vector2(16,16);
	Mix_PlayChannel(-1,deathSound,0);
	
}