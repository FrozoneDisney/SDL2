#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "WinRen.hpp"
#include "Entity.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL INIT FAILED, ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG INIT HAS FAILED, ERROR: " << SDL_GetError() << std::endl;

	WinRen window("Test 1.0", 1280, 720);

	SDL_Texture* player = window.loadTex("player.png");

	std::vector<Entity> entities = {Entity(0, 0, player),
									Entity(100, 100, player),
									Entity(300, 300, player)};
	{
		Entity test(100, 50, player);
		entities.push_back(test);
	}

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

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