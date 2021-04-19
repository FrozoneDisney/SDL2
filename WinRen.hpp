#pragma once
#include <SDL.h>
#include <iostream>

#include "Entity.hpp"

class WinRen
{
public:
	WinRen(const char* p_title, int p_w, int p_h);
	void cleanUp();
	SDL_Texture* loadTex(const char* p_fpath);
	SDL_Texture* loadText(const char* p_fpath, int p_score);

	int getRefreshRate();

	void clear();
	void render(Entity& p_entity);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};