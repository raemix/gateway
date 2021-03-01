#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Entity.hpp"
#include <sstream>
#include <string>
#include <vector>
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

class Tilemap{
public:
	void loadTilemap(const char* filePath);
	std::pair<std::vector<Entity>,Vector2> createEntities();
private:
	std::string map;
	std::vector<Entity> entities;
};