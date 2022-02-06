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

    player = new PhysicsObject(POType::default_, Vec2(-3.f,1.f));
    auto temp = new PhysicsObject(POType::default_static, Vec2(10.f,7.f));
    temp->angle = -32.f;
    temp->torque = -1.f;
    platforms.push_back(temp);
    temp = new PhysicsObject(POType::default_static, Vec2(7.f,5.f));
    temp->angle = 15.f;
    temp->torque = 1.7f;
    platforms.push_back(temp);
    player->ang_vel = 60;
    player->vel = Vec2(2.f, 0.6666f);
}

void Game::GameLoop(const float &dt){
    time += dt;
    
    PhysicsObject::CollisionUpdateAll(dt);
    PhysicsObject::PhysicsUpdateAll(dt);
    std::cout << "time: " << time << std::endl;
}