#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"
#include <sstream>
#include <string>
#include <vector>
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

class Tilemap{
public:
	Tilemap(const char* filePath);
	std::vector<Entity> createEntities(RenderWindow* win);
private:
	std::string map;
	std::vector<Entity> entities;
};