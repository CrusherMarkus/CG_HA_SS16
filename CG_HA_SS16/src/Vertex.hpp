//
//  Vertex.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "Vector.hpp"

class Vertex {
public:
    Vector position;
    Vector normal;
    float texCoordS;
    float texCoordT;
    GLuint *materialIdentifier;
    
public:
    Vertex();
    Vertex(const Vector& p, const Vector& n, float texS, float texT, GLuint *materialIdentifier);
};

#endif /* Vertex_hpp */
