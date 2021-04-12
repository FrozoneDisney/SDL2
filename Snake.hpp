#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Entity.hpp"

class Snake : public Entity
{
public:
	Snake(Vector2f p_pos, SDL_Texture* p_tex);
	void move();
	void changeDir(Vector2f newDir);
	Vector2f getDir();
	void genBody(int p_count);
	bool notHead(std::vector<Snake> p_parts);
	bool isInFront(std::vector<Snake> p_parts);
	void isAligned(std::vector<Snake> p_parts);
	Vector2f getAdd();
	void die();

private:
	float speed;
	Vector2f dir = Vector2f(1, 0);

};
