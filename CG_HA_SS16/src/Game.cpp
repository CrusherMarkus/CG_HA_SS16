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
    
    m_Vehicle.load("objs/tank-camou.obj");
    
}

list<Projektil*> Game::getProjektils() {
    return projektils;
}

void Game::spawnProjektil()
{
    // Aktuelle Position des Vehicles
    Vector vehiclePosition = m_Vehicle.getPosition();
    
    // Startposition des Projektils
    Vector projektilPosition = *new Vector(vehiclePosition.X, vehiclePosition.Y+1.1, vehiclePosition.Z+2.1);
    
    // Richtung der Z-Achse
    Vector direction = *new Vector(0,0,1);
    direction = direction.normalize();
    //projektilPosition.Z += direction.Z;
    
    if(projektils.size() < 5) {
    projektils.push_back(new Projektil(projektilPosition, direction));
    }
}

void Game::gameLoop() {
   
    /*Spiellogik*/
    gameLogic();
    
    /*Timer aktualisieren*/
    g_Timer.calcTime();
    float deltaTimeInSeconds = g_Timer.getDeltaTimeInSeconds();
    
    m_Vehicle.update(deltaTimeInSeconds);
    m_Vehicle.draw();

    g_Camera.apply();
    
    // Projektile
    for (list<Projektil*>::const_iterator it = (projektils).begin(); it != (projektils).end();)
    {
        (**it).draw(deltaTimeInSeconds);
        
      /*
        cout << "(**it).getPosition().length()" << (**it).getPosition().length() << endl;
        cout << "(**it).getMaxDistance()" << (**it).getMaxDistance() << endl;
     */
        
        if((**it).getPosition().length() >= (**it).getMaxDistance()) {
            projektils.pop_front();
        }
        ++it;
    }
    spawnEnemies(deltaTimeInSeconds);
    
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

