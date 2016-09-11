//
//  Vertex.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vertex.hpp"

Vertex::Vertex() {
    
}

Vertex::Vertex(const Vector& p, const Vector& n, float texS, float texT, GLuint *materialIdentifier) {
    this->position = p;
    this->normal = n;
    this->texCoordS = texS;
    this->texCoordT = texT;
    this->materialIdentifier = materialIdentifier;
}