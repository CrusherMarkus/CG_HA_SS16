//
//  ObjParser.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ObjParser_hpp
#define ObjParser_hpp

#include <stdio.h>
#include <map>

#include <fstream>
#include <cassert>
#include "Material.hpp"
#include "ObjModel.hpp"
#include <boost/filesystem.hpp>

using namespace std;

class ObjParser {
private:
    Material *materials;
    int materialCount;
    boost::filesystem::path currentWorkingDirectory;
    
public:
    ObjParser();
    ~ObjParser();
    
    ObjModel *loadModelFromFile(const std::string &pathAndFilename);
    
private:
    void reset();
    void loadMaterial(const char *materialPathAndFilename, std::map<std::string, unsigned int> &materialMap);
};

#endif /* ObjParser_hpp */
