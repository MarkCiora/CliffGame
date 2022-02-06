#include "Game.h"

#include <exception>

Game::Game(){
    time = 0;
    player = nullptr;
    ResetGame();
}

void Game::ResetGame(){
    time = 0;
    delete player;
    for (auto &it : platforms) delete it;
    platforms.clear();

    player = new PhysicsObject(POType::default_, Vec2(3.f,1.f));
    auto temp = new PhysicsObject(POType::default_static, Vec2(10.f,7.f));
    temp->angle += 0.1f;
    platforms.push_back(temp);
}

void Game::GameLoop(const float &dt){
    time += dt;
    
    PhysicsObject::CollisionUpdateAll(dt);
    PhysicsObject::PhysicsUpdateAll(dt);
    std::cout << "time: " << time << std::endl;
}