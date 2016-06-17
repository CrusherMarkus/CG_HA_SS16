//
//  Projektil.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Projektil.hpp"

Projektil::Projektil()
{
    
}

Projektil::~Projektil()
{
    delete this->position;
}

Vector Projektil::getPosition(){
    return *this->position;
}

Vector Projektil::getDirection(){
    
    return *this->direction;
}


Projektil::Projektil(Vector position, Vector direction){
    this->position = new Vector(position.X,position.Y,position.Z);
    this->direction = new Vector(direction.X,direction.Y,direction.Z);
    this->maxDistance = 10.0f;
}

float Projektil::getMaxDistance() {
    return maxDistance;
}

void Projektil::draw(float time){
    time = time;
    
    this->position->Z += this->direction->Z * time;

    glPushMatrix();
    glTranslatef(this->position->X,this->position->Y,this->position->Z);
    
    // built-in (glut library) function , draw you a sphere.
    glutSolidSphere(0.1,25,25);
    glPopMatrix();

}
