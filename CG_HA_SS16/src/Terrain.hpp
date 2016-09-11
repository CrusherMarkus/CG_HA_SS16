//
//  Terrain.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include <stdio.h>
#include "AbstractModel.hpp"
#include "Vector.hpp"
#include "Texture.hpp"
#include <vector>
#include <math.h>

struct TerrainVertex {
    Vector Pos;
    Vector Normal;
    float u0, v0;
    float u1, v1;
};

class Terrain : public AbstractModel {
protected:
    std::vector<TerrainVertex> vertices;
    std::vector<unsigned int> indices;
    Vector dimensions;
    Texture detailMap1;
    Texture detailMap2;
    Texture mixMap;
    Texture shadowTexture;
    unsigned int heightMapImageWidth;
    unsigned int heightMapImageHeight;
    
public:
    Terrain();
    ~Terrain();
    
    std::vector<TerrainVertex> &getVertices();
    void setVertices(std::vector<TerrainVertex> &vertices);
    std::vector<unsigned int> &getIndices();
    void setIndices(std::vector<unsigned int> &indices);
    const Vector &getDimensions() const;
    void setDimensions(const Vector &dimensions);
    Texture &getDetailMap1();
    Texture &getDetailMap2();
    Texture &getMixMap();
    unsigned int getHeightMapImageWidth();
    void setHeightMapImageWidth(unsigned int heightMapImageWidth);
    unsigned int getHeightMapImageHeight();
    void setHeightMapImageHeight(unsigned int heightMapImageHeight);
    
    void draw() const;
    
protected:
    void bindTextures();
    void unbindTextures();
};

#endif /* Terrain_hpp */
