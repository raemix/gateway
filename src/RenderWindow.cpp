#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"
#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
	:window(NULL), renderer(NULL), width(width),height(height){
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if(window==NULL){
		std::cout << "Window could not initialize. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 32, 21, 51, 255);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_RenderSetLogicalSize(renderer, 128, 128);
}

SDL_Texture* RenderWindow::LoadTexture(const char* filePath){
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer,filePath);

	if(texture == NULL){
		std::cout << "Texture could not initialize. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

int RenderWindow::getRefreshRate(){
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex,0,&mode);
	return mode.refresh_rate;
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& ent)
{
	SDL_Rect src;
	src = {ent.getCurrentFrame().x,ent.getCurrentFrame().y,ent.getCurrentFrame().w,ent.getCurrentFrame().h};

	SDL_Rect dst;
	dst = {(int)ent.getPos().x,(int)ent.getPos().y,ent.getCurrentFrame().w,ent.getCurrentFrame().h};

	SDL_RenderCopy(renderer,ent.getTex(),&src,&dst);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}

RenderWindow::~RenderWindow(){
	SDL_DestroyWindow(window);
}