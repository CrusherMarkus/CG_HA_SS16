//
//  ShaderManager.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "ShaderManager.hpp"



ShaderManager::ShaderManager() {
    this->isInitialized = false;
}

ShaderManager::~ShaderManager() {
    this->shaders.clear();
}

#pragma mark - Getter/setter

ShaderProgram *ShaderManager::getShader(const char *shaderName) {
    if (!this->isInitialized) {
        this->initializeShaders();
    }
    
    std::map<std::string, ShaderProgram *>::iterator shaderIterator = this->shaders.find(std::string(shaderName));
    if (shaderIterator == this->shaders.end()) {
        char errorMessage[256];
        sprintf(errorMessage, "No shader with name %s defined!", shaderName);
        throw Exception(errorMessage);
    }
    
    return this->shaders[shaderName];
}

void ShaderManager::initializeShaders() {
    const Vector *lightPosition = new Vector(0, 15, 0);
    const Vector lightColor(1.f, 1.f, 1.f);
    
    // default shader for all scene objects
    ShaderProgram *defaultShader = new ShaderProgram();
    defaultShader->attach(GL_VERTEX_SHADER, "shader/Basic.vertexshader.glsl");
    defaultShader->attach(GL_FRAGMENT_SHADER, "shader/Blinn.fragmentshader.glsl");
    std::string compilerErrorMessage;
    if (defaultShader->compile(&compilerErrorMessage)) {
        defaultShader->activate();
        defaultShader->setParameter(defaultShader->getParameterIdentifier("LightPos"), *lightPosition);
        defaultShader->setParameter(defaultShader->getParameterIdentifier("LightColor"), lightColor);
        defaultShader->deactivate();
    } else {
        throw Exception(compilerErrorMessage.c_str());
    }
    this->shaders.insert(std::pair<std::string, ShaderProgram *>("default", defaultShader));
    
    // terrain shader
    ShaderProgram *terrainShader = new ShaderProgram();
    terrainShader->attach(GL_VERTEX_SHADER, "shader/Basic.vertexshader.glsl");
    terrainShader->attach(GL_FRAGMENT_SHADER, "shader/TextureCombiner.fragmentshader.glsl");
    compilerErrorMessage = std::string();
    if (terrainShader->compile(&compilerErrorMessage)) {
        terrainShader->activate();
        terrainShader->setParameter(terrainShader->getParameterIdentifier("LightPos"), *lightPosition);
        terrainShader->setParameter(terrainShader->getParameterIdentifier("LightColor"), lightColor);
        terrainShader->deactivate();
    } else {
        throw Exception(compilerErrorMessage.c_str());
    }
    this->shaders.insert(std::pair<std::string, ShaderProgram *>("terrain", terrainShader));
    
    // special debug shader which renders normals
    ShaderProgram *debugShader = new ShaderProgram();
    debugShader->attach(GL_VERTEX_SHADER, "shader/NormalDebug.vertexshader.glsl");
    debugShader->attach(GL_FRAGMENT_SHADER, "shader/NormalDebug.fragmentshader.glsl");
    debugShader->attach(GL_GEOMETRY_SHADER_EXT, "shader/NormalDebug.geometryshader.glsl");
    debugShader->setLinkerParameter(GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES);
    debugShader->setLinkerParameter(GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_LINE_STRIP);
    debugShader->setLinkerParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 6);
    compilerErrorMessage = std::string();
    if (!debugShader->compile(&compilerErrorMessage)) {
        throw Exception(compilerErrorMessage.c_str());
    }
    this->shaders.insert(std::pair<std::string, ShaderProgram *>("debug", debugShader));
    
    this->isInitialized = true;
}