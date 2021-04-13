
#include "Snake.hpp"
#include <cmath>



Snake::Snake(Vector2f p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

void Snake::move()
{
	Vector2f tenp(getPos().x + dir.x, getPos().y + dir.y);
	setPos(tenp);
}

void Snake::changeDir(Vector2f newdir)
{
	dir.x = newdir.x;
	dir.y = newdir.y;

	if (newdir.x >= 1)
		setAngle(90);

	if (newdir.x <= -1)
		setAngle(270);

	if (newdir.y >= 1)
		setAngle(180);

	if (newdir.y <= -1)
		setAngle(0);
}

Vector2f Snake::getDir()
{
	return dir;
}

bool Snake::isInFront(std::vector<Snake> p_parts)
{
	for (int i = 0; i < p_parts.size(); i++)
	{
		if (p_parts[i].getPos().x == getPos().x && p_parts[i].getPos().y == getPos().y)
		{
		
			if (p_parts[i - 1.0].getDir().x != getDir().x && p_parts[i - 1.0].getDir().y != getDir().y)
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
	}
	return false;
}

bool Snake::notHead(std::vector<Snake> p_parts)
{
	if (p_parts[0].getPos().y != getPos().y || p_parts[0].getPos().x != getPos().x)
		return true;

	return false;
}

void Snake::isAligned(std::vector<Snake> p_parts)
{
	for (int i = 0; i < p_parts.size(); i++)
	{
		if (p_parts[i].getPos().x == getPos().x && p_parts[i].getPos().y == getPos().y)
		{
			std::cout << p_parts[i - 1.0].getPos().x << ", " << getPos().x << std::endl;
			if(floor(p_parts[i - 1.0].getPos().y) == floor(getPos().y) || floor(p_parts[i - 1.0].getPos().x) == floor(getPos().x))
				changeDir(p_parts[i - 1.0].getDir());
		}
	}
}

Vector2f Snake::getAdd()
{
	if (dir.x >= 1)
		return Vector2f(getPos().x - 32, getPos().y);

	if (dir.x <= -1)
		return Vector2f(getPos().x + 32, getPos().y);
	
	if (dir.y <= 1)
		return Vector2f(getPos().x, getPos().y + 32);

	if (dir.y >= -1)
		return Vector2f(getPos().x, getPos().y - 32);
}
