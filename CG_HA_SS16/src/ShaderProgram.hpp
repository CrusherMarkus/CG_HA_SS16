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
#include <iostream>
#include <string>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include <fstream>

#include "Vector.hpp"
#include "Color.hpp"
#include "Matrix.hpp"

using namespace std;

class ShaderProgram{
public:
    ShaderProgram();
    ~ShaderProgram();
    bool load (const char* VertexShader, const char* FragmentShader);
    bool loadVertexShader(const char* VertexShader);
    bool loadFragmentShader(const char* FragmentShader);
    bool compile(string* CompileErrors = NULL);
    
    GLint getParameterID(const char* ParameterName) const;
    
    void setParameter(GLint ID, float Param);
    void setParameter(GLint ID, int Param);
    void setParameter(GLint ID, const Vector& Param);
    void setParameter(GLint ID, const Color& Param);
    void setParameter(GLint ID, const Matrix& Param);
    
    void activate() const;
    void deactivate() const;
    
private:
    bool loadFile(char* &Buffer, const char* FilePath, GLint &Size);
    bool checkShaderError(GLuint Shader, string* CompileErrors);
    
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ShaderProgram;
};

#endif /* ShaderProgram_hpp */
