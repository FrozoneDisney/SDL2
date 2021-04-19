#include <cmath>
#include "Math.hpp"
#include "Apple.hpp"

Apple::Apple(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex)
{}

void Apple::respawn()
{
    Vector2f temp = Vector2f((rand() % 1472 + 32), (rand() % 800 + 32));
    setPos(temp);
}