#pragma once

#include "Math.hpp"
#include "Entity.hpp"

class Anchor : public Entity
{
public:

	Anchor(Vector2f p_pos, Vector2f p_dir, SDL_Texture* p_tex)
		:Entity(p_pos, p_tex), dir(p_dir)
	{}

	Vector2f getDir();

private:
	Vector2f dir;
};