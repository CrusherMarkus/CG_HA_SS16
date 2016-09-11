//
//  Projektil.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Projektil_hpp
#define Projektil_hpp

#include <stdio.h>
#include <iostream>
#include "Vector.hpp"
#include <math.h>
#include <GLUT/GLUT.h>

using namespace std;

class Projektil
{
public:
    Projektil();
    virtual ~Projektil();
    Projektil(Vector position, Vector direction);
    void draw(float time);
    Vector getPosition();
    Vector getDirection();
    float getMaxDistance();
    
protected:
private:
    float maxDistance;
    Vector* startPosition;
    Vector* position;
    Vector* direction;
};

#endif /* Projektil_hpp */
