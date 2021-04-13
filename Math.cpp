#include "Math.hpp"



bool Vector2f::operator== (Vector2f p_2)
{
	if (x == p_2.x && y == p_2.y)
		return true;
	return false;
}

bool Vector2f::operator!= (Vector2f p_2)
{
	if (x == p_2.x && y == p_2.y)
		return false;
	return true;
}