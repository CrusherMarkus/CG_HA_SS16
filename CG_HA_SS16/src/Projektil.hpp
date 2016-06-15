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
#include "Vector.hpp"
#include <math.h>
#include <GLUT/GLUT.h>

class Projektil
{
public:
    Projektil();
    virtual ~Projektil();
    Projektil(Vector position, Vector direction);
    void draw(float time);
    Vector getPosition();
    Vector getDirection();
    
protected:
private:
    
    Vector* startPosition;
    Vector* position;
    Vector* direction;
};

#endif /* Projektil_hpp */
