#include "Tilemap.hpp"
#include "Main.hpp"
#include "RenderWindow.hpp"
#include "Player.hpp"

void Tilemap::loadTilemap(const char* filePath){
	map = "";
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

std::pair<std::vector<Entity>,Vector2> Tilemap::createEntities(){
	Vector2 portalPos;
	entities.clear();
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
        SDL_Texture* texture = window.LoadTexture(x);
        entities.push_back(Entity(Vector2((float)z*16+16,(float)y*16+16),texture));
        switch(map[i]){
        	case '2':
        		entities[i].setCollidable(true);
        		break;
        	case '4':
        		entities[i].setGoal(true);
        		entities[i].setAnimatable(true,5);
        		break;
        	case '3':
        		portalPos = entities[i].getPos();
        		break;
        }
    }
    return {entities,portalPos};
}