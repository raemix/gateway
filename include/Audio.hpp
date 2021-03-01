#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Audio{
public:
	void start(int frequency, Uint16 format, int channels, int chunksize);
	Mix_Music* LoadMusic(const char* filePath);
	Mix_Chunk* LoadChunk(const char* filePath);
	~Audio();
};