#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "Audio.hpp"

Audio::Audio(int frequency, Uint16 format, int channels, int chunksize){
	if(Mix_OpenAudio(frequency,format,channels,chunksize) < 0){
		std::cout << "Audio could not initialize. Error: " << Mix_GetError() << std::endl; 
	}
}

Mix_Music* Audio::LoadMusic(const char* filePath){
	Mix_Music* music = NULL;
	music = Mix_LoadMUS(filePath);

	if(music == NULL){
		std::cout << "Music could not initialize. Error: " << Mix_GetError() << std::endl;
	}
	return music;
}

Mix_Chunk* Audio::LoadChunk(const char* filePath){
	Mix_Chunk* chunk = NULL;
	chunk = Mix_LoadWAV(filePath);

	if(chunk == NULL){
		std::cout << "Chunk could not initialize. Error: " << Mix_GetError() << std::endl;
	}
	return chunk;
}

Audio::~Audio(){
	Mix_Quit();
}