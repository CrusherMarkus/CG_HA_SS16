//
//  Game.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Vehicle.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"
#include <list>
#include <GLUT/GLUT.h>
#include <chrono>
#include <iostream>
#include <random>


extern Timer g_Timer;
extern Camera g_Camera;

using namespace std;
using namespace std::chrono;

class Game
{
public:
    int enemySpawnTime;
    float spawnTime;
    float spawnTimer;
    Game();
    ~Game();
    vector<Enemy*> enemies;
    void initialize();
	void gameLoop();
    void gameLogic();
    void spawnEnemies(float deltatime);
    bool gameOver;
    
    Vehicle m_Vehicle;
    Enemy m_Enemy;
    
protected:
private:

};
#endif /* Game_hpp */
