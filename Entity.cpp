#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}
void Entity::setTex(SDL_Texture* p_tex)
{
	tex = p_tex;
}
SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

int Entity::getAngle()
{
	return angle;
}

void Entity::setAngle(int p_angle)
{
	angle = p_angle;
}

