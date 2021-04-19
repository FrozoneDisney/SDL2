#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "WinRen.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Snake.hpp"
#include "Apple.hpp"
#include "Anchor.hpp"


class GameMan
{
public:
	void init();
private:
	SDL_Texture* player;
	SDL_Texture* body;
	SDL_Texture* anchor;
	SDL_Texture* apple;
	SDL_Texture* tail;
	SDL_Texture* text;
	int score = 0;
};