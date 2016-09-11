//
//  Explosion.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Explosion_hpp
#define Explosion_hpp

#include <stdio.h>
#include "Vector.hpp"
#include <GLUT/GLUT.h>

class Explosion
{
public:
    Explosion();
    Explosion(Vector& position);
    virtual ~Explosion();
    void draw(float time);
    bool endExplosion;
protected:
private:
    float timeElapsed;
    Vector position;
};

#endif /* Explosion_hpp */
