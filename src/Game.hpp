#pragma once
#include "Camera.hpp"
#include "Hud.hpp"

struct Game
{
    Camera* camera;

    Game(Camera* c)
    {
        camera = c;
    }
};