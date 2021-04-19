#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "WinRen.hpp"
#include "Entity.hpp"

WinRen::WinRen(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, 300, 160, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init, error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void WinRen::cleanUp()
{
	SDL_DestroyWindow(window);
}

SDL_Texture* WinRen::loadTex(const char* p_fpath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_fpath);

	if (texture == NULL)
		std::cout << "Failed to load texture, error: " << SDL_GetError() << std::endl;

	return texture;
}

SDL_Texture* WinRen::loadText(const char* p_fpath, int p_score)
{
	TTF_Font* retro = TTF_OpenFont(p_fpath, 24);
	SDL_Color White = { 255, 255 ,255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(retro, "Score: ", White);
	SDL_Texture* ret = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	return ret;
}

int WinRen::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex( window );

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void WinRen::clear()
{
	SDL_RenderClear(renderer);
}

void WinRen::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), NULL, SDL_FLIP_NONE);
}

void WinRen::display()
{
	SDL_RenderPresent(renderer);
}