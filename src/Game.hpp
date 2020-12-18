#pragma once
#include "FreeflyCamera.hpp"
#include "Hud.hpp"

struct Game
{
    FreeflyCamera* camera;
    Hud* hud;

    Game(FreeflyCamera* c, Hud* h)
    {
        hud = h;
        camera = c;
    }
};