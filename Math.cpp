#include "Math.hpp"
#include "SDL.h"



bool Vector2f::operator== (Vector2f p)
{
	if (x == p.x && y == p.y)
		return true;
	return false;
}

bool Vector2f::operator!= (Vector2f p)
{
	if (x == p.x && y == p.y)
		return false;
	return true;
}

//incorrect lesser than or equal to, only used to check the "dir" of the snake
bool Vector2f::operator<= (Vector2f p)
{
	if (x == p.x && y == p.y)
		return true;

	if (x < p.x || y < p.y)
		return true;

	return false;
}


//incorrect greater than or equal to, only used to check the "dir" of the snake
bool Vector2f::operator>= (Vector2f p)
{
	if (x == p.x && y == p.y)
		return true;

	if (x > p.x || y > p.y)
		return true;

	return false;
}

Vector2f Vector2f::operator* (float p)
{
	return Vector2f(x * p, y * p);
}

Vector2f Vector2f::operator- (Vector2f p)
{
	return Vector2f(x - p.x, y - p.y);
}

