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
    return *position;
}

Vector Projektil::getDirection(){
    
    return *this->direction;
}


Projektil::Projektil(Vector position, Vector direction){
    this->position = new Vector(position.X,position.Y,position.Z);
    this->direction = new Vector(direction.X,direction.Y,direction.Z );
}


void Projektil::draw(float time){
    time = time* 5;
    this->position->Z += this->direction->Z * time;
    

    glPushMatrix();
    glTranslatef(this->position->X,this->position->Y,this->position->Z);
    
    glutSolidCone(0.5, 1, 20, 2);
    glPopMatrix();
    
}
