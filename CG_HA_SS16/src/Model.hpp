//
//  Model.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <iostream>
#include "Vector.hpp"
#include "Color.hpp"
#include <string>
#include <map>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Material.hpp"
#include "ShaderProgram.hpp"


extern const Vector g_LightPos;

struct Vertex
{
    Vertex();
    Vertex( const Vector& p, const Vector& n, float TexS, float TexT, Material* material);
    Vector Position;
    Vector Normal;
    float  TexcoordS;
    float  TexcoordT;
    Material* Material;
};

class BoundingBox
{
public:
    BoundingBox();		
    BoundingBox( const Vector& min, const Vector& max);
    Vector Min;
    Vector Max;
};

class Model
{
public:
    Model();
    ~Model();
    const BoundingBox& boundingBox() const;
    bool load( const char* Filename, const char* VertexShader, const char* FragmentShader, bool FitSize=true);
    void drawLines() const;
    void drawTriangles();
protected:
    void createCube();
    Material* m_pMaterials;
    unsigned int m_MaterialCount;
    Vertex* m_pVertices;
    unsigned int m_VertexCount;
    BoundingBox m_Box;
    ShaderProgram shader;
    void createBoundingBox(std::vector<Vector> vertices);
    void createModel(const char* filename, bool fitSize);
    void loadMaterial(const char* filename, std::map<std::string, int> &materialMap);
private:
};

#endif /* Model_hpp */
