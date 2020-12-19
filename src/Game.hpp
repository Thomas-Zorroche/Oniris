#pragma once
#include "Camera.hpp"
#include "Hud.hpp"

struct Game
{
    Camera* camera;
    Hud* hud;

    Game(Camera* c, Hud* h)
    {
        hud = h;
        camera = c;
    }
};