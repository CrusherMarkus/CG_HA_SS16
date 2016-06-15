//
//  ModelBuilder.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ModelBuilder_hpp
#define ModelBuilder_hpp

#include <stdio.h>
#include <map>
#include <string>
#include "ObjModel.hpp"
#include "ObjParser.hpp"
#include "Model.hpp"

using namespace std;

class ModelBuilder {
    
private:
    std::map<std::string, ObjModel *> cachedObjModels;
    
public:
    ModelBuilder();
    ~ModelBuilder();
    
    Model *buildModel(const std::string &name, const std::string &modelPathAndFilename);
};

#endif /* ModelBuilder_hpp */
