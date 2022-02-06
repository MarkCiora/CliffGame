#pragma once

#include "PhysicsObject.h"
#include "helper.h"
#include "Tex.h"

#include <iostream>
#include <vector>

class Game{
public:
    Game();
    void ResetGame();
    void GameLoop(const float &dt);
    
    float time;
    
    PhysicsObject* player;
    std::vector<PhysicsObject*> others;
    std::vector<PhysicsObject*> platforms;
};