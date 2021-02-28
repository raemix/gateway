#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Math.hpp"
#include "Entity.hpp"
#include <vector>
#include <string>

class Player : public Entity{
private:
	std::vector<Entity> entities;
	Mix_Chunk* moveSound;
	Mix_Chunk* teleportSound;
	Mix_Chunk* deathSound;
	int moves;
	std::vector<Vector2> portalPositions;
	int currentPortal = 0;
	int moveCounts[1] = {6};
	int currentLevel = 0;
	// int state;
public:
	Player(Vector2 pos, SDL_Texture* tex,Mix_Chunk* moveSound,Mix_Chunk* teleportSound,Mix_Chunk* deathSound);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	const char* getMoves();
	bool checkMoves();
	void setEntities(std::vector<Entity>* entities);
	void portalPushBack(Vector2 position);
	void teleport();
	void restart();
	// int getState();
	// void setState(int state);
	// enum movement_states {
 //  		IDLE, MOVING_UP, MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT
	// };
};