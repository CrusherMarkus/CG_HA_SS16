//
//  Explosion.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Explosion.hpp"

Explosion::Explosion()
{
    this->endExplosion = false;
    this->timeElapsed = 0;
}

Explosion::~Explosion()
{
}

Explosion::Explosion(Vector& position){
    this->endExplosion = false;
    this->timeElapsed = 0;
    this->position =  Vector(position.X,position.Y,position.Z );;
}

void Explosion::draw(float time){
    this->timeElapsed = this->timeElapsed + time;
    if (this->timeElapsed >= 1)
    {
        this->endExplosion = true;
    }
    else{
        glColor3d(1,1-timeElapsed,0);
        glPushMatrix();
        glTranslatef(this->position.X,this->position.Y,this->position.Z);
        glRotatef(90,0,1,0);
        glutSolidSphere(timeElapsed/3, 20, 20);
        glPopMatrix();
    }
    
}