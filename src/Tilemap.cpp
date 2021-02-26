#include "Tilemap.hpp"
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

Tilemap::Tilemap(const char* filePath){
	{
	    rapidxml::file<> xmlFile(filePath);
	    // dump document on heap
	    rapidxml::xml_document<>* doc = new rapidxml::xml_document<>();
	    doc->parse<0>(xmlFile.data());
	    rapidxml::xml_node<>* node = doc->first_node("map")->first_node("layer")->first_node("data");

	    std::stringstream ss;
	    ss << *node;


	    for (unsigned int i = 0; i < ss.str().length(); i++) {
	        if (std::isdigit(ss.str()[i])) map += ss.str()[i];
	    }

	    delete doc;
	}
}

std::vector<Entity> Tilemap::createEntities(RenderWindow* win){
    int y = -1;
    unsigned int z = 0;
    for (unsigned int i = 0; i < map.size(); i++) {
        if (i % 6 == 0) {
            y++;
            z = 0;
        }
        else z++;
        char x[] = "res/gfx/tile .png";
        x[12] = map[i]-1;
        SDL_Texture* texture = win->LoadTexture(x);
        entities.push_back(Entity(Vector2((float)z*16,(float)y*16),texture));
        if(map[i] == '2'){
        	entities[i].setCollidable(true);
        }
    }
    return entities;
}