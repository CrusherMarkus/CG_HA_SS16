//
//  ModelBuilder.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ModelBuilder_hpp
#define ModelBuilder_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "Model.hpp"
#include "Terrain.hpp"
#include "ObjModel.hpp"
#include "ObjParser.hpp"
#include "Texture.hpp"
#include "RGBImage.hpp"

class ModelBuilder {
    
private:
    std::map<std::string, ObjModel *> cachedObjModels;
    
public:
    ModelBuilder();
    ~ModelBuilder();
    
    Model *buildModel(const char* Filename);
    Terrain *buildTerrain(const char *heightMap, const char *detailMap1, const char *detailMap2, const char *mixMap, float width, float depth, float heightMultiplier);
};

#endif /* ModelBuilder_hpp */
