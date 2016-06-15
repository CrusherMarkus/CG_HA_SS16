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
    cout << "Game::initialize" << endl;
    
    m_Vehicle.load("objs/FA-22_Raptor.obj", Vector(0,0,-3), "shader/vertex.glsl", "shader/fragment_blin.glsl");
}



void Game::spawnProjektil()
{
    
    Vector playerPosition = m_Vehicle.getPosition();
    cout << "playerPosition->X: " << playerPosition.X << endl;
    cout << "playerPosition->Y: " << playerPosition.Y << endl;
    cout << "playerPosition->Z: " << playerPosition.Z << endl;
    
    
    Vector* projectilePosition = new Vector(playerPosition.X, playerPosition.Y, playerPosition.Z);
    Vector* direction = new Vector(0,0,1);
    *direction = direction->normalize();
    
    projectilePosition->Z += direction->Z;
    
    cout << "projectilePosition->X: " << projectilePosition->X << endl;
    cout << "projectilePosition->Y: " << projectilePosition->Y << endl;
    cout << "projectilePosition->Z: " << projectilePosition->Z << endl;
    
    projektils.push_back(new Projektil(*projectilePosition, *direction));
}

void Game::gameLoop() {
   
    /*Spiellogik*/
    //gameLogic();
    
    /*Timer aktualisieren*/
    g_Timer.calcTime();
    float deltaTimeInSeconds = g_Timer.getDeltaTimeInSeconds();
    
    
    m_Vehicle.update(deltaTimeInSeconds);
    m_Vehicle.draw();

    g_Camera.apply();
    
    
    glColor3d(0,1,0);
    for (list<Projektil*>::const_iterator it = (projektils).begin(); it != (projektils).end();)
    {

        (**it).getPosition().X;
        (**it).draw(deltaTimeInSeconds);
        ++it;
    }
    
    
}

void Game::gameLogic() {
    

    

}
