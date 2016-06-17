//
//  ShaderProgram.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "ShaderProgram.hpp"

#include "ShaderProgram.hpp"
#include <fstream>
#include <vector>

ShaderProgram::ShaderProgram() {
    
}

ShaderProgram::~ShaderProgram() {
    
}

GLint ShaderProgram::getParameterIdentifier(const char *parameterName) const {
    return glGetUniformLocation(this->shaderProgram, parameterName);
}

void ShaderProgram::setParameter(GLint identifier, float parameter) {
    glUniform1f(identifier, parameter);
}

void ShaderProgram::setParameter(GLint identifier, int parameter) {
    glUniform1i(identifier, parameter);
}

void ShaderProgram::setParameter(GLint identifier, const Vector &parameter) {
    glUniform3f(identifier, parameter.X, parameter.Y, parameter.Z);
}

void ShaderProgram::setParameter(GLint identifier, const Color &parameter) {
    glUniform3f(identifier, parameter.R, parameter.G, parameter.B);
}

void ShaderProgram::setParameter(GLint identifier, const Matrix &parameter ) {
    glUniformMatrix4fv(identifier, 1, GL_FALSE, (float *)&parameter);
}

bool ShaderProgram::load(const char *vertexShaderPathAndFilename, const char *fragmentShaderPathAndFilename) {
    bool isVertexShaderLoaded = this->loadVertexShader(vertexShaderPathAndFilename);
    if (!isVertexShaderLoaded) {
        return false;
    }
    
    bool isFragmentShaderLoaded = this->loadFragmentShader(fragmentShaderPathAndFilename);
    if (!isFragmentShaderLoaded) {
        return false;
    }
    
    return true;
}

bool ShaderProgram::loadVertexShader(const char *vertexShaderPathAndFilename) {
    return this->loadShaderCodeFromFile(vertexShaderPathAndFilename, &this->vertexShaderCode);
}

bool ShaderProgram::loadFragmentShader(const char *fragmentShaderPathAndFilename) {
    return this->loadShaderCodeFromFile(fragmentShaderPathAndFilename, &this->fragmentShaderCode);
}

bool ShaderProgram::compile(std::string *compileErrorMessage) {
    if (this->vertexShaderCode == "" && this->fragmentShaderCode == "") {
        std::cout << "Load at least one shader file before compiling";
        return false;
    }
    
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::cout << "Compiling shaders... ";
    bool isVertexShaderCompiled = false;
    bool isFragementShaderCompiled = false;
    if (this->vertexShaderCode != "") {
        isVertexShaderCompiled = this->compileShader(this->vertexShader, &this->vertexShaderCode, compileErrorMessage);
        if (!isVertexShaderCompiled) {
            return false;
        }
    }
    if (this->fragmentShaderCode != "") {
        isFragementShaderCompiled = this->compileShader(this->fragmentShader, &this->fragmentShaderCode, compileErrorMessage);
        if (!isFragementShaderCompiled) {
            return false;
        }
    }
    std::cout << "Done!" << std::endl;
    
    std::cout << "Linking shaders... ";
    this->shaderProgram = glCreateProgram();
    if (isVertexShaderCompiled) {
        glAttachShader(this->shaderProgram, this->vertexShader);
    }
    if (isFragementShaderCompiled) {
        glAttachShader(this->shaderProgram, this->fragmentShader);
    }
    glLinkProgram(this->shaderProgram);
    
    GLint linkResult = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &linkResult);
    glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> linkErrors(infoLogLength);
    glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, &linkErrors[0]);
    if (linkResult == GL_FALSE && compileErrorMessage != NULL) {
        *compileErrorMessage = std::string(&linkErrors[0]);
        return false;
    }
    std::cout << "Done!" << std::endl;
    
    std::cout << "Shader compilation completed without errors." << std::endl;
    
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    
    return true;
}

void ShaderProgram::activate() const {
    glUseProgram(this->shaderProgram);
}

void ShaderProgram::deactivate() const {
    glUseProgram(0);
}

bool ShaderProgram::loadShaderCodeFromFile(const char *shaderPathAndFilename, std::string *shaderCode) {
    std::ifstream shaderStream(shaderPathAndFilename, std::ios::in);
    
    if (!shaderStream.is_open()) {
        std::cout << "Could not open " << shaderPathAndFilename << std::endl;
        return false;
    }
    
    std::cout << "Loading " << shaderPathAndFilename << "...";
    
    std::string line = "";
    while(getline(shaderStream, line)) {
        *shaderCode += "\n" + line;
    }
    shaderStream.close();
    
    std::cout << " Done!" << std::endl;
    
    return true;
}

bool ShaderProgram::compileShader(GLuint shaderIdentifier, std::string *shaderCode, std::string *compileErrorMessage) {
    GLint compileResult = GL_FALSE;
    int infoLogLength;
    
    char const *shaderSourcePointer = shaderCode->c_str();
    glShaderSource(shaderIdentifier, 1, &shaderSourcePointer , NULL);
    glCompileShader(shaderIdentifier);
    
    glGetShaderiv(shaderIdentifier, GL_COMPILE_STATUS, &compileResult);
    glGetShaderiv(shaderIdentifier, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> compilerErrors(infoLogLength);
    glGetShaderInfoLog(shaderIdentifier, infoLogLength, NULL, &compilerErrors[0]);
    
    if (compileResult == GL_FALSE && compileErrorMessage != NULL) {
        *compileErrorMessage = std::string(&compilerErrors[0]);
    }
    
    return compileResult == GL_TRUE;
}

