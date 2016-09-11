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
    
    Vector *startpos = new Vector(0, 0, 0);
    
    m_Vehicle.load("objs/tank_bottom.obj","objs/tank_top.obj",*startpos);
    
}



void Game::gameLoop() {
   
    /*Spiellogik*/
    gameLogic();
    
    /*Timer aktualisieren*/
    g_Timer.calcTime();
    float deltaTimeInSeconds = g_Timer.getDeltaTimeInSeconds();
    
    m_Vehicle.update(deltaTimeInSeconds);
    m_Vehicle.updateProjektils(deltaTimeInSeconds);
    m_Vehicle.draw();

    g_Camera.apply();
    

    //spawnEnemies(deltaTimeInSeconds);
    
}


void Game::gameLogic() {


    

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

