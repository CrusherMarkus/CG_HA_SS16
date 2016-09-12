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
    this->spawnTime = 60;
    this->spawnTimer = 0;
}

Game::~Game()
{
    
}

void Game::initialize(){
    cout << "Game::initialize()" << endl;

    gl::hp = 100;
    m_Vehicle.load("objs/tank_bottom.obj","objs/tank_top.obj",*new Vector(0, 0, -10));
        

    //m_Enemy.load("objs/tank-camou.obj",*new Vector(0,0,-10));
    m_DefenseObject.load("objs/gingerbreadhouse.obj", *new Vector(0,0,0));
    
    //ModelBuilder modelBuilder;
    //terrain = modelBuilder.buildTerrain("tex/heightmap.bmp", "tex/sand.bmp", "tex/grass.bmp", "tex/mixmap.bmp", 60, 60, 0);
    
}

void Game::gameLoop() {
    
    // Spiellogik
    gameLogic();
    
    // Timer aktualisieren
    g_Timer.calcTime();
    float deltaTimeInSeconds = g_Timer.getDeltaTimeInSeconds();
    
    // Vehicle
    m_Vehicle.update(deltaTimeInSeconds);
    m_Vehicle.updateProjektils(deltaTimeInSeconds);
    m_Vehicle.updateExplosions(deltaTimeInSeconds);
    
    m_Vehicle.draw();
    
    // Gegner
    //m_Enemy.update(deltaTimeInSeconds);
    //m_Enemy.draw();
    spawnEnemies(deltaTimeInSeconds);
    
    // Verteidigung
    m_DefenseObject.update(deltaTimeInSeconds);
    m_DefenseObject.draw();
    
    // Terrain erstellen
    //terrain->draw();
    
    collision();
    
    // Camera Position updaten
    m_Camera.update(m_Vehicle.getPosition(), m_Vehicle.getModelViewMatrix().right(), 7.0f, m_Vehicle.getPosition().Y + 3.0f, 4.0f, deltaTimeInSeconds);
    m_Camera.apply();
}


void Game::gameLogic() {
    
    /*if(m_DefenseObject.getHp() <= 0){
     restartGame();
     }*/
}

int Game::getEnemySize(){
    return this->enemies.size();
}


void Game::spawnEnemies(float deltatime){
    this->spawnTimer -= deltatime*3;
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
            
            while(x > -15 && x <= 15 ){
                x = distr(eng);
            }
            while (z > -15 && z <= 15 ){
                z = distr(eng);
            }

            tmp = new Enemy();
            Vector ePos = *new Vector(x,0,z);
            tmp->load("objs/tank-camou.obj", ePos);
            enemies.push_back(tmp);
            
        }
        
    }
    
    
}

void Game::collision(){
    BoundingBox tank = m_Vehicle.newBB;
    for(int i=0; i < enemies.size(); i++){
        
        //Check Collision between Tank and Enemies
        BoundingBox tmp = enemies.at(i)->newBB;

       enemies.at(i)->setIsHit((tank.getMin().X <= tmp.getMax().X && tank.getMax().X >= tmp.getMin().X) &&
        (tank.getMin().Y <= tmp.getMax().Y && tank.getMax().Y >= tmp.getMin().Y) &&
        (tank.getMin().Z <= tmp.getMax().Z && tank.getMax().Z >= tmp.getMin().Z));
        
        // Check Collision between Projectile Spheres and Enemies
        if(!enemies.at(i)->getIsHit()){
            

          for (int j =0; j< m_Vehicle.getProjektils().size();j++){
              float a= max(tmp.getMin().X, min(m_Vehicle.getProjektils().at(j)->getPosition().X, tmp.getMax().X));
              float b = max(tmp.getMin().Y, min(m_Vehicle.getProjektils().at(j)->getPosition().Y,tmp.getMax().Y));
              float c = max(tmp.getMin().Z,min(m_Vehicle.getProjektils().at(j)->getPosition().Z,tmp.getMax().Z));
        
              float distance = sqrt((a - m_Vehicle.getProjektils().at(j)->getPosition().X) * (a - m_Vehicle.getProjektils().at(j)->getPosition().X) +
                                    (b - m_Vehicle.getProjektils().at(j)->getPosition().Y) * (b - m_Vehicle.getProjektils().at(j)->getPosition().Y) +
                                    (c - m_Vehicle.getProjektils().at(j)->getPosition().Z) * (c - m_Vehicle.getProjektils().at(j)->getPosition().Z));
        
              enemies.at(i)->setIsHit(distance < 0.3);
          }
        }
        
    }
}

void Game::restartGame(){
    std::cout << "Game::restartGame" << std::endl;
    
    
    this->startGame();
    
}

void Game::startGame(){
    std::cout << "Game::startGame" << std::endl;
    this->initialize();
}
