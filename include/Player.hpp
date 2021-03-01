#pragma once
#include "Entity.hpp"
#include "Math.hpp"
#include "Main.hpp"

class Player : public Entity{
public:
	Player(Vector2 pos, SDL_Texture* tex,Mix_Chunk* moveSound,Mix_Chunk* teleportSound,Mix_Chunk* deathSound);
	void newPosition(Vector2 targetPosition);
	const char* getMoves();
	bool checkMoves();
	void setEntities(std::vector<Entity>* entities);
	void setPortalPosition(Vector2* portalPosition);	
	void teleport();
	void restart();
private:
	std::vector<Entity> entities;
	Vector2 portalPosition;
	Mix_Chunk* moveSound;
	Mix_Chunk* teleportSound;
	Mix_Chunk* deathSound;
	int moves;
	int moveCounts[2] = {6,6};
	int currentLevel;
};