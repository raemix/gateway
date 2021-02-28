#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.hpp"

class RenderWindow{
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* LoadTexture(const char* filePath);
	int getRefreshRate();
	void clear();
	void render(Entity& ent);
	void render(float x, float y, SDL_Texture* tex);
	void render(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float x, float y, SDL_Texture* tex);
	void display();
	~RenderWindow();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
};