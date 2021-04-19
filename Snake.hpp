#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Entity.hpp"

class Snake : public Entity
{
public:
	Snake(Vector2f p_pos, SDL_Texture* p_tex, float p_speed);
	void move();
	void changeDir(Vector2f newDir);
	Vector2f getDir();
	float getSpeed();
	void updateSpeed(float p_multiplier);
	bool notHead(std::vector<Snake> p_parts);
	bool isInFront(std::vector<Snake> p_parts);
	void isAligned(std::vector<Snake> p_parts);
	Vector2f getAdd();
	void die();

private:
	float speed;
	Vector2f dir = Vector2f(1, 0);
	std::vector<Vector2f> anchorList;

};
