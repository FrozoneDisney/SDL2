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
	void setPos(Vector2f& p_pos)
	{
		pos = p_pos;
	}
	SDL_Texture* getTex();
	void setTex(SDL_Texture* p_tex);
	SDL_Rect getCurrentFrame();
	int getAngle();
	void setAngle(int p_angle);
	
private: 
	int angle = 0;
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;

};
