#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "WinRen.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Snake.hpp"
#include "Apple.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL INIT FAILED, ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG INIT HAS FAILED, ERROR: " << SDL_GetError() << std::endl;

	WinRen window("Test 1.0", 1280, 720);

	SDL_Texture* player = window.loadTex("player.png");
	SDL_Texture* body = window.loadTex("body.png");
	SDL_Texture* anchor = window.loadTex("bodyanch.png");
	SDL_Texture* apple = window.loadTex("apple.png");

	Apple edible(Vector2f(600, 350), apple);

	std::vector<Snake> entities = { Snake(Vector2f(532.0f, 0.0f), player), Snake(Vector2f(499.0f, 0.0f), body), Snake(Vector2f(466.0f, 0.0f), body),Snake(Vector2f(433.0f, 0.0f), body) };
	bool gameRunning = true;


	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	for (Snake& e : entities)
	{
		e.changeDir(Vector2f(3, 0));
	}

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
				if (keystates[SDL_SCANCODE_E])
				{
					entities.push_back(Snake(entities.back().getAdd(), body));
					entities.back().changeDir(entities[entities.size() - 2].getDir());
				
				}
				if (keystates[SDL_SCANCODE_R])
				{
					edible.respawn();
				}
			}
			for (Snake& e : entities)
			{
				if (e.notHead(entities))
				{
					if (e.isInFront(entities))
					{
						e.setTex(anchor);
						e.isAligned(entities);
					}
				}
				e.move();
			}
			if(entities[0].getPos().x >= edible.getPos().x - 16 && entities[0].getPos().x <= edible.getPos().x + 16 && entities[0].getPos().y >= edible.getPos().y - 16 && entities[0].getPos().y <= edible.getPos().y + 16 )
			{
				edible.respawn();
				entities.push_back(Snake(entities.back().getAdd(), body));
				entities.back().changeDir(entities[entities.size() - 2].getDir());
			}
			
			accumulator -= timeStep;
		}


		

		window.clear();
		
		for (Entity& ent : entities)
		{
			window.render(ent);
		}
		window.render(edible);

		
		
		window.display();

	}

	window.cleanUp();
	SDL_Quit();
	return 0;
}