//
//  Game.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Game.hpp"

Game::Game()
{
    this->spawnTime = 20;
    this->spawnTimer = 0;
}

Game::~Game()
{

}

void Game::initialize(){
    cout << "Game::initialize()" << endl;
    
    Vector *startpos = new Vector(0, 0, -3);
    
    m_Vehicle.load("objs/tank_bottom.obj","objs/tank_top.obj",*startpos);
    m_Enemy.load("objs/tank-camou.obj",*new Vector(20,0,20));
    m_DefenseObject.load("objs/cylinder.obj", *new Vector(1,0,1));

    //ModelBuilder modelBuilder;
    //terrain = modelBuilder.buildTerrain("tex/heightmap.bmp", "tex/sand.bmp", "tex/grass.bmp", "tex/mixmap.bmp", 60, 60, 0);
    
}



void Game::gameLoop() {
   
    /*Spiellogik*/
    gameLogic();
    
    /*Timer aktualisieren*/
    g_Timer.calcTime();
    float deltaTimeInSeconds = g_Timer.getDeltaTimeInSeconds();
    
    // Vehicle
    m_Vehicle.update(deltaTimeInSeconds);
    m_Vehicle.updateProjektils(deltaTimeInSeconds);
    m_Vehicle.updateExplosions(deltaTimeInSeconds);
    m_Vehicle.draw();
    
    // Gegner
    m_Enemy.update(deltaTimeInSeconds);
    m_Enemy.draw();
    //spawnEnemies(deltaTimeInSeconds);
   
    // Verteidigung
    m_DefenseObject.update(deltaTimeInSeconds);
    m_DefenseObject.draw();
    
    // Terrain erstellen
    //terrain->draw();

    g_Camera.apply();
    
}


void Game::gameLogic() {


    

}

int Game::getEnemySize(){
    return this->enemies.size();
}


void Game::spawnEnemies(float deltatime){
    this->spawnTimer -= deltatime*3;
    //cout << "spawntimer:"<< this->spawnTimer << endl;
    if (gameOver){
        return;
    }else {
        for(int i = 0; i < enemies.size(); i++){
            if (enemies.at(i)->getIsHit()){
                Enemy *tmp = enemies.at(i);
                enemies.erase(enemies.begin()+i);
                delete (tmp);
            }else {
                enemies.at(i)->update(deltatime);
                enemies.at(i)->draw();
            }
        }
        
        if (spawnTimer <= 0){
            spawnTimer = this->spawnTime;
            Enemy *tmp;
            

            random_device rd; // obtain a random number from hardware
            mt19937 eng(rd()); // seed the generator
            uniform_int_distribution<int> distr(-30, 30); // define the range
        
            int x = 0;
            int z = 0;
            
            while(x > -5 && x <= 5 ){
                x = distr(eng);
                cout << "x: "<< x<< endl;
            }
            while (z > -5 && z <= 5 ){
                z = distr(eng);
                cout << "z: "<< z<< endl;
            }

            cout << "x:"<<x <<" z="<< z << endl;

            tmp = new Enemy();
            Vector ePos = *new Vector(x,0,z);
            tmp->load("objs/tank-camou.obj", ePos);
            enemies.push_back(tmp);
            
        }
        
    }
        
}

