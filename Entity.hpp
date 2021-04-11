#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	Vector2f& getPos()
	{
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void move();
	void changeDir(Vector2f newDir);
private: 
	Vector2f pos;
	Vector2f dir = Vector2f(1, 0);

	SDL_Rect currentFrame;
	SDL_Texture* tex;

};
