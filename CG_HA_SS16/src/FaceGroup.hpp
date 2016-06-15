//
//  FaceGroup.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef FaceGroup_hpp
#define FaceGroup_hpp

#include <stdio.h>

#include "AbstractModel.hpp"
#include "Vertex.hpp"
#include <vector>

using namespace std;

class FaceGroup : public AbstractModel {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Material *material;
    Texture whiteTexture;
    
    FaceGroup();
    
    void draw() const;
};

#endif /* FaceGroup_hpp */
