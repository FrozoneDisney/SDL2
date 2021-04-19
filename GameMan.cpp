#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "WinRen.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Snake.hpp"
#include "Apple.hpp"
#include "Anchor.hpp"
#include "GameMan.hpp"

void GameMan::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL INIT FAILED, ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG INIT HAS FAILED, ERROR: " << SDL_GetError() << std::endl;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		std::cout << "AUDIO INIT HAS FAILED, ERROR: " << SDL_GetError() << std::endl;

	WinRen window("Snake", 1536, 864);

	player = window.loadTex("player.png");
	body = window.loadTex("body.png");
	anchor = window.loadTex("bodyanch.png");
	apple = window.loadTex("apple.png");
	tail = window.loadTex("tail.png");
	text = window.loadText("Retro.ttf", score);


	Apple edible(Vector2f(600, 350), apple);

	std::vector<Anchor> anchors;
	std::vector<Snake> entities = { Snake(Vector2f(532.0f, 50.0f), player, 2), Snake(Vector2f(500.0f, 50.0f), body, 2), Snake(Vector2f(468.0f, 50.0f), body, 2),Snake(Vector2f(436.0f, 50.0f), tail, 2) };
	std::vector<Entity> gameObjects;
	Entity scoretext = Entity(Vector2f(50, 50), text);
	for (int i = 0; i < 1536 / 32; i++)
	{
		gameObjects.push_back(Entity(Vector2f(i * 32, 0), anchor));
		gameObjects.push_back(Entity(Vector2f(i * 32, 864 - 32), anchor));
	}
	for (int i = 0; i < 864 / 32; i++)
	{
		gameObjects.push_back(Entity(Vector2f(0, i * 32), anchor));
		gameObjects.push_back(Entity(Vector2f(1536 - 32, i * 32), anchor));
	}
	bool gameRunning = true;

	SDL_Event event;

	float cooldown = 0;
	float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	Snake* head = &entities[0];
	for (Snake& e : entities)
	{
		e.changeDir(Vector2f(1, 0));
	}

	while (gameRunning)
	{
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;
		cooldown -= frameTime;

		while (accumulator >= timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
				if (keystates[SDL_SCANCODE_DOWN] && entities[0].getAngle() != 0 && entities[0].getAngle() != 180 && cooldown <= 0)
				{
					cooldown = 0.05;
					entities[0].changeDir(Vector2f(0, 1));
					anchors.push_back(Anchor(entities[0].getPos(), entities[0].getDir(), anchor));
				}
				if (keystates[SDL_SCANCODE_UP] && entities[0].getAngle() != 0 && entities[0].getAngle() != 180 && cooldown <= 0)
				{
					cooldown = 0.05;
					entities[0].changeDir(Vector2f(0, -1));
					anchors.push_back(Anchor(entities[0].getPos(), entities[0].getDir(), anchor));
				}
				if (keystates[SDL_SCANCODE_LEFT] && entities[0].getAngle() != 270 && entities[0].getAngle() != 90 && cooldown <= 0)
				{
					cooldown = 0.05;
					entities[0].changeDir(Vector2f(-1, 0));
					anchors.push_back(Anchor(entities[0].getPos(), entities[0].getDir(), anchor));
				}
				if (keystates[SDL_SCANCODE_RIGHT] && entities[0].getAngle() != 270 && entities[0].getAngle() != 90 && cooldown <= 0)
				{
					cooldown = 0.05;
					entities[0].changeDir(Vector2f(1, 0));
					anchors.push_back(Anchor(entities[0].getPos(), entities[0].getDir(), anchor));
				}
				if (keystates[SDL_SCANCODE_E])
				{
					entities.push_back(Snake(entities.back().getAdd(), body, entities[0].getSpeed()));
					entities.back().changeDir(entities[entities.size() - 2].getDir());

				}
			}


			for (Snake& e : entities)
			{
				if (e.notHead(entities))
				{
					for (int a = 0; a < (int)anchors.size(); a++)
					{
						if (utils::smallCollisionCheck(e.getPos(), anchors[a].getPos()))
						{
							e.setPos(anchors[a].getPos());
							e.changeDir(anchors[a].getDir());
							if (e.getPos() == entities.back().getPos())
								anchors.erase(anchors.begin() + a);
						}
					}
					if (utils::collisionCheck(entities[0].getPos(), e.getPos()) && entities[1].getPos() != e.getPos())
						gameRunning = false;
				}

				e.move();
			}
			if (utils::collisionCheck(entities[0].getPos(), edible.getPos()))
			{
				SDL_DestroyTexture(text);
				score++;
				window.loadText("Retro.ttf", score);
				edible.respawn();
				entities.back().setTex(body);
				entities.push_back(Snake(entities.back().getAdd(), body, entities[0].getSpeed()));
				entities.back().changeDir(entities[entities.size() - 2].getDir());
				entities.push_back(Snake(entities.back().getAdd(), tail, entities[0].getSpeed()));
				entities.back().changeDir(entities[entities.size() - 2].getDir());
				for (Snake& e : entities)
				{
					if (timeStep > 0.005f)
						timeStep *= 0.999f;
				}
			}
			for (Entity& e : gameObjects)
			{
				if (utils::collisionCheck(entities[0].getPos(), e.getPos()))
					gameRunning = false;
			}


			accumulator -= timeStep;
		}

		std::cout << timeStep << std::endl;

		window.clear();


		for (Anchor& anc : anchors)
		{
			window.render(anc);
		}

		for (Entity& ent : entities)
		{
			window.render(ent);
		}

		for (Entity& ent : gameObjects)
		{
			window.render(ent);
		}




		window.render(edible);

		window.render(scoretext);
		window.display();

	}

	window.cleanUp();
	SDL_Quit();
}