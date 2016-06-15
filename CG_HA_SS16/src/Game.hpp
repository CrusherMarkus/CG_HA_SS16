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
#include "Projektil.hpp"
#include <list>
#include <GLUT/GLUT.h>


extern Timer g_Timer;
extern Camera g_Camera;

using namespace std;

class Game
{
public:
    Game();
    ~Game();

    void initialize();
	void gameLoop();
    void gameLogic();
    void spawnProjektil();
    Vehicle m_Vehicle;
    
    list<Projektil*> projektils;


protected:
private:

};
#endif /* Game_hpp */
