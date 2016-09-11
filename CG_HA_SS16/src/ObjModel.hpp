//
//  ObjModel.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ObjModel_hpp
#define ObjModel_hpp

#include "Vector.hpp"

#include <stdio.h>
#include <vector>

class Material;

struct TextureCoordinate {
    float s,t;
};

struct Face {
    unsigned int pidx[3], tidx[3];
    unsigned int materialIdentifier;
};

class ObjModel {
public:
    ObjModel();
    
    std::vector<Vector> positions;
    std::vector<TextureCoordinate> textureCoordinates;
    std::vector<Face> faces;
    Material *materials;
    int materialCount;
};

#endif /* ObjModel_hpp */
