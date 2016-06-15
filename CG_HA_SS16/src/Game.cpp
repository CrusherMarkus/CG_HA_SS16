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
    
    m_Vehicle.load("objs/tank-camou.obj", Vector(0,0,0), "shader/vertex.glsl", "shader/fragment_blin.glsl");
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
    /*Camera Position updaten*/
    /*m_Camera.update(m_Vehicle.getPosition(), m_Vehicle.getModelViewMatrix().forward(), 7.0f, m_Vehicle.getPosition().Y + 3.0f, 4.0f, deltaTimeInSeconds);
    m_Camera.apply();*/
}

void Game::gameLogic() {
    

    

}
