#pragma once

#include<SDL.h>

static class utils
{
public:
	static inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;

	}

	static bool collisionCheck(Vector2f p_1, Vector2f p_2)
	{
		SDL_Rect rect1 = { p_1.x, p_1.y, 32, 32 };
		SDL_Rect rect2 = { p_2.x, p_2.y, 32, 32 };

		if (SDL_bool collision = SDL_HasIntersection(&rect1, &rect2))
			return true;
		return false;
	}

	static bool smallCollisionCheck(Vector2f p_1, Vector2f p_2)
	{
		SDL_Rect rect1 = { p_1.x, p_1.y, 1, 1 };
		SDL_Rect rect2 = { p_2.x, p_2.y, 1, 1 };

		if (SDL_bool collision = SDL_HasIntersection(&rect1, &rect2))
			return true;
		return false;
	}

	static float distance(Vector2f p_1, Vector2f p_2)
	{
		Vector2f substr = p_2 - p_1;
		return sqrtf(pow(substr.x, 2) - pow(substr.y, 2));
	}
};