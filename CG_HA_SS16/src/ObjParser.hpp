//
//  ObjParser.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ObjParser_hpp
#define ObjParser_hpp

#include <stdio.h>

#include <vector>
#include <map>

class ObjModel;
class Material;

class ObjParser {
private:
    Material *materials;
    int materialCount;
    
public:
    ObjParser();
    ~ObjParser();
    
    ObjModel *loadModelFromFile(const char* Filename);
    
private:
    void reset();
    void loadMaterial(const char *materialPathAndFilename, std::map<std::string, unsigned int> &materialMap);
};

#endif /* ObjParser_hpp */
