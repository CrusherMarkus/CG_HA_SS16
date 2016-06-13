//
//  ShaderProgram.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() {
}

ShaderProgram::~ShaderProgram() {
}

bool ShaderProgram::load (const char* VertexShader, const char* FragmentShader) {
    return this->loadVertexShader(VertexShader) && this->loadFragmentShader(FragmentShader);
}

bool ShaderProgram::loadVertexShader(const char* VertexShader) {
    GLint fileSize;
    char *shader;
        
    if (!loadFile(shader, VertexShader, fileSize))
    {
        cerr << "Vertex Shader nicht geladen (" << VertexShader << ")" << endl;
        return false;
    }
    
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertexShader, 1, &shader, &fileSize);
    
    return true;
}

bool ShaderProgram::loadFragmentShader(const char* FragmentShader) {
    GLint fileSize;
    char *shader;
    
    if (!loadFile(shader, FragmentShader, fileSize))
    {
        cerr << "Fragment Shader nicht geladen (" << FragmentShader << ")" << endl;
        return false;
    }
    
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragmentShader, 1, &shader, &fileSize);
    
    return true;
}

bool ShaderProgram::compile(string* CompileErrors) {
    // compile vertex shader
    glCompileShader(m_VertexShader);
    if (!checkShaderError(m_VertexShader, CompileErrors))
        return false;
    
    // compile fragment shader
    glCompileShader(m_FragmentShader);
    if (!checkShaderError(m_FragmentShader, CompileErrors))
        return false;
    
    m_ShaderProgram = glCreateProgram();
    
    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);
    
    glLinkProgram(m_ShaderProgram);
    
    GLint isLinked = 0;
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_ShaderProgram, maxLength, &maxLength, &infoLog[0]);
        
        glDeleteProgram(m_ShaderProgram);
        
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);
        
        CompileErrors->append(&infoLog[0]);
        
        return false;
    }
    
    glDetachShader(m_ShaderProgram, m_VertexShader);
    glDetachShader(m_ShaderProgram, m_FragmentShader);
    
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
    
    return true;
}

GLint ShaderProgram::getParameterID(const char* ParameterName) const {
    return glGetUniformLocation(m_ShaderProgram, ParameterName);
}

void ShaderProgram::setParameter(GLint ID, float Param) {
    glUniform1f(ID, Param);
}

void ShaderProgram::setParameter(GLint ID, int Param) {
    glUniform1i(ID, Param);
}

void ShaderProgram::setParameter(GLint ID, const Vector& Param) {
    glUniform3f(ID, Param.X, Param.Y, Param.Z);
}

void ShaderProgram::setParameter(GLint ID, const Color& Param) {
    glUniform3f(ID, Param.R, Param.G, Param.B);
}

void ShaderProgram::setParameter(GLint ID, const Matrix& Param) {
    glUniformMatrix4fv(ID, 1, GL_FALSE, Param.m);
}

void ShaderProgram::activate() const {
    glUseProgram(m_ShaderProgram);
}

void ShaderProgram::deactivate() const {
    glUseProgram(0);
}

bool ShaderProgram::loadFile(char* &Buffer, const char* FilePath, GLint &Size) {
    ifstream file(FilePath, ios::binary | ios::ate);
    
    if(!file.is_open())
        return false;
    
    Size = (GLint) file.tellg();
    file.seekg(0, ios::beg);
    
    Buffer = (char*) malloc(sizeof(char) * Size);
    
    if(!file.read(Buffer, (long)Size))
        return false;
    
    file.close();
    
    return true;
}

bool ShaderProgram::checkShaderError(GLuint Shader, string* CompileErrors) {
    GLint success = 0;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    
    if(success == GL_FALSE) {
        GLint logLength = 0;
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &logLength);
        
        if(logLength == 0) {
            CompileErrors->append("Error compiling shader. No error message found.");
            
            return false;
        }
        
        vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(Shader, logLength, NULL, &errorLog[0]);
        
        CompileErrors->append(&errorLog[0]);
        
        glDeleteShader(Shader);
        
        return false;
    }
    
    return true;
}
