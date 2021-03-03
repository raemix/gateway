#include "../include/Player.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/Audio.hpp"
#include "../include/Main.hpp"
#include <iostream>

Player::Player(Vector2 pos, SDL_Texture* tex, Mix_Chunk* moveSound,Mix_Chunk* teleportSound, Mix_Chunk* deathSound) : Entity(pos, tex){
	this->moveSound = moveSound;
	this->teleportSound = teleportSound;
	this->deathSound = deathSound;
	currentLevel++;
	moves = moveCounts[currentLevel-1];
}
void Player::newPosition(Vector2 targetPosition){
	for(Entity& e : entities){
		if(targetPosition.x == e.getPos().x && targetPosition.y == e.getPos().y){
			if(e.getCollidable() == false && e.getGoal()){
				currentLevel++;
				pos = targetPosition;
				moves -= 1;
				Mix_PlayChannel(-1,moveSound,0);
				std::string x = std::to_string(currentLevel);
				x = "res/dev/tilemap"+ x + ".tmx";
				loadLevel(x.c_str());
				pos = Vector2(16,16);
				moves = moveCounts[currentLevel-1];
				break;
			}else if (e.getCollidable() == false){
				pos = targetPosition;
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
	this->entities.clear();
	this->entities = *entities;
}

void Player::setPortalPosition(Vector2* portalPosition){
	this->portalPosition = *portalPosition;
}

void Player::teleport(){
	pos = portalPosition;
	Mix_PlayChannel(-1,teleportSound,0);
}

void Player::restart(){
	moves = moveCounts[currentLevel-1];
	pos = Vector2(16,16);
	Mix_PlayChannel(-1,deathSound,0);
}
