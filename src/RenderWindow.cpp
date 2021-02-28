#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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


void RenderWindow::render(float x, float y, SDL_Texture* tex){
	SDL_Rect src{0,0};
	SDL_QueryTexture(tex, NULL, NULL, &src.w, &src.h); 

	SDL_Rect dst{(int)x,(int)y,src.w,src.h};

	SDL_RenderCopy(renderer, tex, &src, &dst);
}

void RenderWindow::render(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor){
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src{0,0,surfaceMessage->w,surfaceMessage->h};
		SDL_Rect dst{(int)x,(int)y,src.w,src.h};

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
}

void RenderWindow::renderCenter(float x, float y, const char* text, TTF_Font* font, SDL_Color textColor){
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); // mfw somebody uses sdl_surfaces for rendering (•ˋ _ ˊ•)

		SDL_Rect src{0,0,surfaceMessage->w,surfaceMessage->h};

		SDL_Rect dst{128/2 - src.w/2 + (int)x,128/2 - src.h/2 + (int)y,src.w,src.h};

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
}

void RenderWindow::renderCenter(float x, float y, SDL_Texture* tex){
	SDL_Rect src{0,0};
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(tex, NULL, NULL, &src.w, &src.h); 

	SDL_Rect dst{128/2 - src.w/2 + (int)x,128/2 - src.h/2 + (int)y,src.w,src.h};

	SDL_RenderCopy(renderer, tex, &src, &dst);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}

RenderWindow::~RenderWindow(){
	SDL_DestroyWindow(window);
}