//
//  Vertex.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vertex.hpp"

Vertex::Vertex()
{
    
}

Vertex::Vertex(const Vector& p, const Vector& n, float TexS, float TexT, GLuint *materialIdentifier)
{
    Position = p;
    Normal = n;
    TexcoordS = TexS;
    TexcoordT = TexT;
    this->materialIdentifier = materialIdentifier;
}