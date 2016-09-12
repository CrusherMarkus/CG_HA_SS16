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
    this->radius=0.1;
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
    this->maxDistance = 7.0f;
    this->distance = 0.0f;
}

float Projektil::getMaxDistance() {
    return maxDistance;
}

void Projektil::draw(float deltatime){
    
    float time = deltatime *5 ;
    if( this->distance < this->maxDistance){
        this->distance += time*1.5;
    }
    
    this->position = new Vector(this->position->X+this->direction->X*time,0.5,this->position->Z+this->direction->Z*time);
    glPushMatrix();
    glTranslatef(this->position->X,this->position->Y,this->position->Z);
    
    // Kugel erzeugen
    glutSolidSphere(0.1,25,25);
    glPopMatrix();
    
}

float Projektil::getDistance(){
    return this->distance;
}
