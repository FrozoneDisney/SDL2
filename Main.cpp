#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "WinRen.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL INIT FAILED, ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG INIT HAS FAILED, ERROR: " << SDL_GetError() << std::endl;

	WinRen window("Test 1.0", 1280, 720);

	SDL_Texture* player = window.loadTex("player.png");

	std::vector<Entity> entities = {Entity(Vector2f(0.0f, 0.0f), player),
									Entity(Vector2f(100.0f, 100.0f), player),
									Entity(Vector2f(300.0f, 300.0f), player)};
	{
		Entity test(Vector2f(100.0f, 50.0f), player);
		entities.push_back(test);
	}

	bool gameRunning = true;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	while (gameRunning)
	{
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
				if (keystates[SDL_SCANCODE_DOWN])
					entities[0].changeDir(Vector2f(0, 3));
				if (keystates[SDL_SCANCODE_UP])
					entities[0].changeDir(Vector2f(0, -3));
				if (keystates[SDL_SCANCODE_LEFT])
					entities[0].changeDir(Vector2f(-3, 0));
				if (keystates[SDL_SCANCODE_RIGHT])
					entities[0].changeDir(Vector2f(3, 0));
			}
			entities[0].move();
			
			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep; 

		

		window.clear();
		
		for (Entity& ent : entities)
		{
			window.render(ent);
		}

		
		
		window.display();

	}

	window.cleanUp();
	SDL_Quit();
	return 0;
}