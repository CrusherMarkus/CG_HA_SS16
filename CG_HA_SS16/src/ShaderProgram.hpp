//
//  ShaderProgram.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>

#include "Vector.hpp"
#include "Color.hpp"
#include "Matrix.hpp"

class ShaderProgram {
private:
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    
public:
    ShaderProgram();
    ~ShaderProgram();
    
    GLint getParameterIdentifier(const char *parameterName) const;
    void setParameter(GLint identifier, float parameter);
    void setParameter(GLint identifier, int parameter);
    void setParameter(GLint identifier, const Vector &parameter);
    void setParameter(GLint identifier, const Color &parameter);
    void setParameter(GLint identifier, const Matrix &parameter);
    
    bool load(const char *vertexShaderPathAndFilename, const char *fragmentShaderPathAndFilename);
    bool loadVertexShader(const char *vertexShaderPathAndFilename);
    bool loadFragmentShader(const char *fragmentShaderPathAndFilename);
    bool compile(std::string *compileErrorMessage = NULL);
    void activate() const;
    void deactivate() const;
    
private:
    bool loadShaderCodeFromFile(const char *shaderPathAndFilename, std::string *shaderCode);
    bool compileShader(GLuint shaderIdentifier, std::string *shaderCode, std::string *compileErrorMessage = NULL);
};
#endif /* ShaderProgram_hpp */
