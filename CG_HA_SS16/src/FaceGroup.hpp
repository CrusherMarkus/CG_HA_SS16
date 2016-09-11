//
//  FaceGroup.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef FaceGroup_hpp
#define FaceGroup_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "AbstractModel.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"

class Material;

class FaceGroup : public AbstractModel {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material *material;
    Texture whiteTexture;
    
    FaceGroup();
    
    void draw() const;
};

#endif /* FaceGroup_hpp */
