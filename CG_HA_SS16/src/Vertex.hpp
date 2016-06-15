//
//  Vertex.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include "Vector.hpp"
#include "Material.hpp"


class Vertex {
public:
    Vertex();
    Vertex( const Vector& p, const Vector& n, float TexS, float TexT, GLuint *materialIdentifier);
    Vector Position;
    Vector Normal;
    float TexcoordS;
    float TexcoordT;
    GLuint *materialIdentifier;
};

#endif /* Vertex_hpp */
