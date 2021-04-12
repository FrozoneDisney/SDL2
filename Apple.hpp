#pragma once
#include "Entity.hpp"

class Apple: public Entity
{
public:

    Apple(Vector2f p_pos, SDL_Texture* p_tex);
    void respawn();
    int getPointValue();
private:
    int pointValue = 1;
};