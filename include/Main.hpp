#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <cmath>

// forward declarations
class RenderWindow;
class Audio;
class Player;
class Tilemap;
class Entity;
class Vector2;
//

// core classes
extern RenderWindow window;
extern Audio mixer;
extern Player character;
extern Tilemap tiles;
//

extern std::vector<Entity> entities;
extern Vector2 portal;


void setEntities();
void handleInput(SDL_Event* event, bool* running);
bool init();
void loop();
void loadLevel(const char* level);
