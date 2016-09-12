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
#include "Terrain.hpp"
#include <list>
#include <GLUT/GLUT.h>
#include <chrono>
#include <iostream>
#include <random>
#include "DefenseObject.hpp"
#include "VehicleCamera.hpp"
#include <Math.h>
extern short HP;
extern Timer g_Timer;
extern Camera g_Camera;
extern DefenseObject m_DefenseObject;

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
    void collision();
    bool gameOver;
    Vehicle m_Vehicle;
    
    Enemy m_Enemy;
    Terrain *terrain;
    
    VehicleCamera m_Camera;

    
    DefenseObject m_DefenseObject;
    
    int getEnemySize();
    
    
protected:
private:

};
#endif /* Game_hpp */
