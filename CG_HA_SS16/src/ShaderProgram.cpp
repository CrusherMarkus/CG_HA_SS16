//
//  ShaderProgram.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "ShaderProgram.hpp"

#include <fstream>
#include <vector>

ShaderProgram::ShaderProgram() {
    this->shaderProgram = glCreateProgram();
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

void ShaderProgram::setParameter(GLint identifier, bool parameter) {
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

void ShaderProgram::setLinkerParameter(GLenum pname, GLint value) {
    glProgramParameteriEXT(this->shaderProgram, pname, value);
}

void ShaderProgram::attach(GLenum type, const char *shaderPathAndFilename) {
    std::string *shaderCode = NULL;
    switch (type) {
        case GL_VERTEX_SHADER:
            shaderCode = &this->vertexShaderCode;
            break;
        case GL_FRAGMENT_SHADER:
            shaderCode = &this->fragmentShaderCode;
            break;
        case GL_GEOMETRY_SHADER_EXT:
            shaderCode = &this->geometryShaderCode;
            break;
        default:
            throw Exception("Unsupported shader type.");
    }
    
    this->loadShaderCodeFromFile(shaderPathAndFilename, shaderCode);
}

bool ShaderProgram::compile(std::string *compileErrorMessage) {
    if (this->vertexShaderCode == "" && this->fragmentShaderCode == "") {
        std::cout << "Load at least one shader file before compiling";
        return false;
    }
    
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    this->geometryShader = glCreateShader(GL_GEOMETRY_SHADER_EXT);
    
    std::cout << "Compiling and linking shaders... ";
    if (this->vertexShaderCode != "") {
        this->compileShader(this->vertexShader, &this->vertexShaderCode, compileErrorMessage);
        glAttachShader(this->shaderProgram, this->vertexShader);
    }
    if (this->fragmentShaderCode != "") {
        this->compileShader(this->fragmentShader, &this->fragmentShaderCode, compileErrorMessage);
        glAttachShader(this->shaderProgram, this->fragmentShader);
    }
    if (this->geometryShaderCode != "") {
        this->compileShader(this->geometryShader, &this->geometryShaderCode, compileErrorMessage);
        glAttachShader(this->shaderProgram, this->geometryShader);
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
    glDeleteShader(this->geometryShader);
    
    return true;
}

void ShaderProgram::activate() const {
    glUseProgram(this->shaderProgram);
}

void ShaderProgram::deactivate() const {
    glUseProgram(0);
}

void ShaderProgram::loadShaderCodeFromFile(const char *shaderPathAndFilename, std::string *shaderCode) {
    std::ifstream shaderStream(shaderPathAndFilename, std::ios::in);
    std::cout << "shaderPathAndFilename" << shaderPathAndFilename <<  std::endl;

    if (!shaderStream.is_open()) {
        char *errorMessage;
        sprintf(errorMessage, "Could not open file %s for reading.", shaderPathAndFilename);
        throw Exception(errorMessage);
    }
    
    std::cout << "Loading " << shaderPathAndFilename << "...";
    
    std::string line = "";
    while(getline(shaderStream, line)) {
        *shaderCode += "\n" + line;
    }
    shaderStream.close();
    
    std::cout << " Done!" << std::endl;
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
