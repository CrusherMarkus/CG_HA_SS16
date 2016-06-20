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

}

Game::~Game()
{

}

void Game::initialize(){
    cout << "Game::initialize()" << endl;
    
    m_Vehicle.load("objs/tank-camou.obj","shader/Basic_vertexshader.glsl", "shader/Blinn_fragmentshader.glsl");
    
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
    cout << "deltaTimeInSeconds" << deltaTimeInSeconds << endl;
    
    float fps = g_Timer.getFPS();
    cout << "fps" << fps << endl;
    
    
    
    
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
    
    
}


void Game::gameLogic() {


    

}
