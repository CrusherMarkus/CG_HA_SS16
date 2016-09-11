//
//  ShaderManager.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include <stdio.h>
#include <map>
#include "ShaderProgram.hpp"
#include "Exception.hpp"


class ShaderManager {
private:
    bool isInitialized;
    std::map<std::string, ShaderProgram *>shaders;
    
public:
    static ShaderManager &getInstance() {
        static ShaderManager instance;
        return instance;
    }
    
    ShaderProgram *getShader(const char *shaderName);
    
private:
    ShaderManager();
    ShaderManager(ShaderManager const&) = delete;
    ~ShaderManager();
    void operator=(ShaderManager const&) = delete;
    
    void initializeShaders();
};

#endif /* ShaderManager_hpp */
