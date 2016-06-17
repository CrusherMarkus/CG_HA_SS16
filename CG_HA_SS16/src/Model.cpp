//
//  Model.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 17.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cfloat>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "Camera.hpp"

#include "Model.hpp"

extern Camera g_Camera;

Vertex::Vertex()
{
    
}

Vertex::Vertex(const Vector& p, const Vector& n, float TexS, float TexT, class Material *material)
{
    Position = p;
    Normal = n;
    TexcoordS = TexS;
    TexcoordT = TexT;
    Material = material;
}

BoundingBox::BoundingBox()
{
}
BoundingBox::BoundingBox( const Vector& min, const Vector& max) : Min(min), Max(max)
{
}

void Model::loadTexture(const char* s) {
    this->texture.LoadFromBMP(s);
}

Model::Model() : m_pVertices(NULL), m_pMaterials(NULL), m_MaterialCount(0), m_VertexCount(0)
{
    m_pMaterials = new Material[30];
    this->shader = new ShaderProgram();
    this->tilingU = 1;
    this->tilingV = 1;
}

Model::~Model()
{
    if( m_pVertices) {
        delete [] m_pVertices;
    }
    
    delete [] m_pMaterials;
    delete this->shader;
}

bool Model::isSelected() const {
    return this->selected;
}

void Model::setSelected(bool isSelected) {
    this->selected = isSelected;
}

bool Model::load(const char* Filename, bool FitSize, const char *vertexShader, const char *fragmentShader) {
    createModel(Filename, FitSize);
    
    if(!this->shader->load(vertexShader, fragmentShader)) {
        return false;
    }
    
    std::string compilerErrorMessage;
    if (this->shader->compile(&compilerErrorMessage)) {
        this->shader->activate();
        this->shader->setParameter(this->shader->getParameterIdentifier("LightPos"), g_Camera.getViewMatrix() * g_LightPos); //Nochmal nachschauen
        this->shader->setParameter(this->shader->getParameterIdentifier("LightColor"), Vector(1.f, 0.f, 0.f));
        this->shader->deactivate();
    } else {
        std::cout << compilerErrorMessage;
        
        return false;
    }
    
    this->whiteTexture.LoadFromBMP("white.bmp");
    
    return true;
}

void Model::createBoundingBox(std::vector<Vector> vertices) {
    g_Camera.apply();
    m_Box.Max.X = m_Box.Min.X = vertices[0].X;
    m_Box.Max.Y = m_Box.Min.Y = vertices[0].Y;
    m_Box.Max.Z = m_Box.Min.Z = vertices[0].Z;
    
    for(int i = 0; i < vertices.size(); i++) {
        Vector vertex = vertices[i];
        
        if(m_Box.Min.X < vertex.X) m_Box.Min.X = vertex.X;
        if(m_Box.Min.Y < vertex.Y) m_Box.Min.Y = vertex.Y;
        if(m_Box.Min.Z < vertex.Z) m_Box.Min.Z = vertex.Z;
        
        if(m_Box.Max.X > vertex.X) m_Box.Max.X = vertex.X;
        if(m_Box.Max.Y > vertex.Y) m_Box.Max.Y = vertex.Y;
        if(m_Box.Max.Z > vertex.Z) m_Box.Max.Z = vertex.Z;
    }
}

void Model::setTiling(int u, int v) {
    this->tilingU = u;
    this->tilingV = v;
}

void Model::showBox() const{
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 1.0, 0.0); //rgb(54%,17%,89%) = lila
    glBegin(GL_LINES);
    
    glVertex3f(m_Box.Min.X, m_Box.Max.Y, m_Box.Min.Z);
    glVertex3f(m_Box.Min.X, m_Box.Max.Y, m_Box.Max.Z);
    
    glVertex3f(m_Box.Min.X, m_Box.Max.Y, m_Box.Max.Z);
    glVertex3f(m_Box.Max.X, m_Box.Max.Y, m_Box.Max.Z);
    
    glVertex3f(m_Box.Max.X, m_Box.Max.Y, m_Box.Max.Z);
    glVertex3f(m_Box.Max.X, m_Box.Max.Y, m_Box.Min.Z);
    
    glVertex3f(m_Box.Max.X, m_Box.Max.Y, m_Box.Min.Z);
    glVertex3f(m_Box.Min.X, m_Box.Max.Y, m_Box.Min.Z);
    
    glVertex3f(m_Box.Min.X, m_Box.Min.Y, m_Box.Min.Z);
    glVertex3f(m_Box.Min.X, m_Box.Min.Y, m_Box.Max.Z);
    
    glVertex3f(m_Box.Min.X, m_Box.Min.Y, m_Box.Max.Z);
    glVertex3f(m_Box.Max.X, m_Box.Min.Y, m_Box.Max.Z);
    
    glVertex3f(m_Box.Max.X, m_Box.Min.Y, m_Box.Max.Z);
    glVertex3f(m_Box.Max.X, m_Box.Min.Y, m_Box.Min.Z);
    
    glVertex3f(m_Box.Max.X, m_Box.Min.Y, m_Box.Min.Z);
    glVertex3f(m_Box.Min.X, m_Box.Min.Y, m_Box.Min.Z);
    
    glVertex3f(m_Box.Min.X, m_Box.Max.Y, m_Box.Min.Z);
    glVertex3f(m_Box.Min.X, m_Box.Min.Y, m_Box.Min.Z);
    
    glVertex3f(m_Box.Min.X, m_Box.Max.Y, m_Box.Max.Z);
    glVertex3f(m_Box.Min.X, m_Box.Min.Y, m_Box.Max.Z);
    
    glVertex3f(m_Box.Max.X, m_Box.Max.Y, m_Box.Max.Z);
    glVertex3f(m_Box.Max.X, m_Box.Min.Y, m_Box.Max.Z);
    
    glVertex3f(m_Box.Max.X, m_Box.Max.Y, m_Box.Min.Z);
    glVertex3f(m_Box.Max.X, m_Box.Min.Y, m_Box.Min.Z);
    
    glEnd();
    glEnable(GL_LIGHTING);
}

void Model::createRectangle(Vector size, Vector pos, const char* VertexShader, const char* FragmentShader, const char* wallpaper)
{
    size.X /= 2;
    size.Y /= 2;
    size.Z /= 2;
    
    Vector PositionsFromFile[8] =
    {
        Vector(pos.X - size.X, pos.Y - size.Y, pos.Z + size.Z),
        Vector(pos.X - size.X,  pos.Y + size.Y, pos.Z + size.Z),
        Vector(pos.X + size.X, pos.Y - size.Y, pos.Z + size.Z),
        Vector(pos.X + size.X,  pos.Y + size.Y, pos.Z + size.Z),
        Vector(pos.X + size.X, pos.Y - size.Y, pos.Z - size.Z),
        Vector(pos.X + size.X,  pos.Y + size.Y, pos.Z - size.Z),
        Vector(pos.X - size.X, pos.Y - size.Y, pos.Z - size.Z),
        Vector(pos.X - size.X, pos.Y + size.Y, pos.Z - size.Z)
    };
    struct Texcoord
    {
        float s, t;
    };
    Texcoord TexcoordFromFile[20] =
    {
        { 0, 1 },
        { 1, 0 },
        { 0, 0 },
        { 0, 0 },
        { 1, 1 },
        { 0, 1 },
        { 1, 1 },
        { 0, 0 },
        { 1, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 1 },
        { 1, 0 },
        { 0, 0 },
        { 1, 1 },
        { 0, 1 },
        { 0, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 1 }
    };
    struct Face
    {
        unsigned int vIndex[3], tIndex[3];
    };
    Face FacesFromFile[12]
    {
        //face 1
        { 3,4,2,   9, 12, 6 },
        { 3,2,1,   9, 6, 3 },
        //face 2
        { 5,6,4,   13,15,11 },
        { 5,4,3,   13,11,8 },
        //face 3
        { 7,8,6,   18,20,16 },
        { 7,6,5,   18,16,14 },
        //face 4
        { 1,2,8,   2,5,19 },
        { 1,8,7,   2,19,17 },
        //face 5
        { 4,6,8,   10,15,19 },
        { 4,8,2,   10,19,4 },
        //face 6
        { 5,3,1,   13,7,1 },
        { 5,1,7,   13,1,17 }
    };
    
    Material* material = new Material();
    material->setName("Grundmaterial");
    material->setAmbientColor(Color(0.1, 0.1, 0.1));
    material->setDiffuseColor(Color(0.3, 0.3, 0.3));
    material->setSpecularColor(Color(0.1, 0.1, 0.1));
    material->setSpecularExponent(4.0);
    material->setDiffuseTexture(wallpaper);
    
    this->m_pMaterials[this->m_MaterialCount++] = *material;
    
    m_pVertices = new Vertex[12 * 3];
    m_VertexCount = 12 * 3;
    for (int i = 0; i<12; i++)
    {
        unsigned int PosIdx0 = FacesFromFile[i].vIndex[0] - 1;
        unsigned int PosIdx1 = FacesFromFile[i].vIndex[1] - 1;
        unsigned int PosIdx2 = FacesFromFile[i].vIndex[2] - 1;
        
        unsigned int TexIdx0 = FacesFromFile[i].tIndex[0] - 1;
        unsigned int TexIdx1 = FacesFromFile[i].tIndex[1] - 1;
        unsigned int TexIdx2 = FacesFromFile[i].tIndex[2] - 1;
        
        Vector a = m_pVertices[i * 3].Position = PositionsFromFile[PosIdx0];
        Vector b = m_pVertices[i * 3 + 1].Position = PositionsFromFile[PosIdx1];
        Vector c = m_pVertices[i * 3 + 2].Position = PositionsFromFile[PosIdx2];
        
        m_pVertices[i * 3].TexcoordS = TexcoordFromFile[TexIdx0].s;
        m_pVertices[i * 3 + 1].TexcoordS = TexcoordFromFile[TexIdx1].s;
        m_pVertices[i * 3 + 2].TexcoordS = TexcoordFromFile[TexIdx2].s;
        
        m_pVertices[i * 3].TexcoordT = TexcoordFromFile[TexIdx0].t;
        m_pVertices[i * 3 + 1].TexcoordT = TexcoordFromFile[TexIdx1].t;
        m_pVertices[i * 3 + 2].TexcoordT = TexcoordFromFile[TexIdx2].t;
        
        Vector normal = (b - a).cross(c - a);
        normal.normalize();
        
        m_pVertices[i * 3].Normal =
        m_pVertices[i * 3 + 1].Normal =
        m_pVertices[i * 3 + 2].Normal = normal;
        
        m_pVertices[i * 3].Material =
        m_pVertices[i * 3 + 1].Material =
        m_pVertices[i * 3 + 2].Material = material;
    }
    
    //Lade den Shader
    if (!shader->load(VertexShader, FragmentShader)) {
        std::cout << "Cannot load Vertex- or FragmentShader:" << VertexShader << " " << FragmentShader << std::endl;
        //sleep(5000);
        exit(-11);
    }
    
    
    std::string compilerErrorMessage;
    if (shader->compile(&compilerErrorMessage)) {
        shader->activate();
        shader->setParameter(shader->getParameterIdentifier("LightPos"), g_LightPos);//Camera
        shader->setParameter(shader->getParameterIdentifier("LightColor"), Vector(1.f, 0.f, 0.f));
        shader->deactivate();
    }
    else {
        std::cout << compilerErrorMessage;
        
        //sleep(5000);
        exit(-12);
    }
}

void Model::createModel(const char* filename, bool fitSize) {
    std::ifstream inStream(filename);
    if (!inStream) {
        std::cout << "Model::createModel:Cannot open file " << filename << std::endl;
        exit(-1);
    }
    
    std::vector<Vector> v;
    
    struct TextureCoordinates {
        float s,t;
    };
    std::vector<TextureCoordinates> t;
    
    struct Face {
        unsigned int pidx[3], tidx[3];
        Material *material = NULL;
    };
    std::vector<Face> f;
    
    std::map<std::string, int> materialMap;
    
    Material *currentMaterial = NULL;
    
    int maxCharactersPerLine = 8192; // should be enough for obj files
    char inputBuffer[maxCharactersPerLine];
    while (inStream.peek() != -1) {
        inStream.getline(&inputBuffer[0], maxCharactersPerLine);
        
        std::string lineBuffer(&inputBuffer[0]);
        
        // Trim newline '\r\n' or '\n'
        if (lineBuffer.size() > 0) {
            if (lineBuffer[lineBuffer.size() - 1] == '\n') {
                lineBuffer.erase(lineBuffer.size() - 1);
            }
        }
        if (lineBuffer.size() > 0) {
            if (lineBuffer[lineBuffer.size() - 1] == '\r') {
                lineBuffer.erase(lineBuffer.size() - 1);
            }
        }
        
        // Skip if empty line.
        if (lineBuffer.empty()) {
            continue;
        }
        
        const char *token = lineBuffer.c_str();
        
        assert(token);
        
        // skip on empty line or comment
        if (token[0] == '\0' || token[0] == '#') {
            continue;
        }
        
        // vertex
        if (token[0] == 'v' && token[1] == ' ') {
            token += 2;
            Vector vertex;
            sscanf(token, "%f %f %f", &vertex.X, &vertex.Y, &vertex.Z);
            v.push_back(vertex);
            continue;
        }
        
        // texture coords
        if (token[0] == 'v' && token[1] == 't') {
            token += 3;
            TextureCoordinates tc;
            sscanf(token, "%f %f", &tc.s, &tc.t );
            t.push_back(tc);
            continue;
        }
        
        /*// face
         if (token[0] == 'f') {
         token += 2;
         
         Face face;
         Face face2;
         unsigned int vertexIndex[4], texIndex[4];
         
         int matches = sscanf(token, "%d/%d %d/%d %d/%d %d/%d", &vertexIndex[0], &texIndex[0], &vertexIndex[1], &texIndex[1], &vertexIndex[2], &texIndex[2], &vertexIndex[3], &texIndex[3]);
         
         face.pidx[0] = vertexIndex[0];
         face.pidx[1] = vertexIndex[1];
         face.pidx[2] = vertexIndex[2];
         face.tidx[0] = texIndex[0];
         face.tidx[1] = texIndex[1];
         face.tidx[2] = texIndex[2];
         face.material = currentMaterial;
         f.push_back(face);
         
         if (matches == 8) {
         face2.pidx[0] = vertexIndex[2];
         face2.pidx[1] = vertexIndex[3];
         face2.pidx[2] = vertexIndex[0];
         face2.tidx[0] = texIndex[2];
         face2.tidx[1] = texIndex[3];
         face2.tidx[2] = texIndex[0];
         face.material = currentMaterial;
         f.push_back(face2);
         }
         
         continue;
         }*/
        
        // face
        if (token[0] == 'f') {
            token += 2;
            
            Face face;
            Face face2;
            int vertexIndex[4] = {1, 1, 1, 1}, texIndex[4] = {1, 1, 1, 1};
            int junk;
            
            int matches = sscanf(token, "%d/%d %d/%d %d/%d %d/%d", &vertexIndex[0], &texIndex[0], &vertexIndex[1], &texIndex[1], &vertexIndex[2], &texIndex[2], &vertexIndex[3], &texIndex[3]);
            if (matches < 6) {
                matches = sscanf(token, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &texIndex[0], &junk, &vertexIndex[1], &texIndex[1], &junk, &vertexIndex[2], &texIndex[2], &junk, &vertexIndex[3], &texIndex[3], &junk);
            }
            
            if (vertexIndex[0] < 0) {
                vertexIndex[0] = (int)v.size() - vertexIndex[0];
                vertexIndex[1] = (int)v.size() - vertexIndex[1];
                vertexIndex[2] = (int)v.size() - vertexIndex[2];
                texIndex[0] = (int)t.size() - texIndex[0];
                texIndex[1] = (int)t.size() - texIndex[1];
                texIndex[2] = (int)t.size() - texIndex[2];
                if (matches == 8) {
                    vertexIndex[3] = (int)v.size() - vertexIndex[3];
                    texIndex[3] = (int)t.size() - texIndex[3];
                }
            }
            
            face.pidx[0] = vertexIndex[0];
            face.pidx[1] = vertexIndex[1];
            face.pidx[2] = vertexIndex[2];
            face.tidx[0] = texIndex[0];
            face.tidx[1] = texIndex[1];
            face.tidx[2] = texIndex[2];
            face.material = currentMaterial;
            f.push_back(face);
            
            if (matches == 8) {
                face2.pidx[0] = vertexIndex[2];
                face2.pidx[1] = vertexIndex[3];
                face2.pidx[2] = vertexIndex[0];
                face2.tidx[0] = texIndex[2];
                face2.tidx[1] = texIndex[3];
                face2.tidx[2] = texIndex[0];
                face.material = currentMaterial;
                f.push_back(face2);
            }
            
            continue;
        }
        
        // mtllib
        if (strncmp(token, "mtllib", 6) == 0) {
            char materialFile[256];
            token += 7;
            sscanf(token, "%s", materialFile);
            std::string filepath(filename);
            filepath = filepath.substr(0, filepath.find_last_of("\\/") + 1);
            
            loadMaterial((filepath + std::string(materialFile)).c_str(), materialMap);
        }
        
        // use mtl
        if (strncmp(token, "usemtl", 6) == 0) {
            char materialName[256];
            token += 7;
            sscanf(token, "%s", materialName);
            std::map<std::string, int>::iterator materialIterator = materialMap.find(std::string(materialName));
            if (materialIterator != materialMap.end()) {
                int materialIndex = materialIterator->second;
                currentMaterial = &this->m_pMaterials[materialIndex];
            }
        }
    }
    
    // create bounding box and scale model if required
    this->createBoundingBox(v);
    if (fitSize) {
        float scale = 10 / ((m_Box.Min - m_Box.Max).length());
        for(int i = 0; i < v.size(); i++){
            v[i] = v[i] * scale;
        }
    }
    
    // assemble vertices and materials from collected data
    int faceCount = (int) f.size();
    m_pVertices = new Vertex[faceCount * 3];
    m_VertexCount = faceCount * 3;
    
    for(int i = 0; i < faceCount; i++) {
        unsigned int PosIdx0 = f[i].pidx[0] - 1;
        unsigned int PosIdx1 = f[i].pidx[1] - 1;
        unsigned int PosIdx2 = f[i].pidx[2] - 1;
        
        unsigned int TexIdx0 = f[i].tidx[0] - 1;
        unsigned int TexIdx1 = f[i].tidx[1] - 1;
        unsigned int TexIdx2 = f[i].tidx[2] - 1;
        
        Vector a = m_pVertices[i * 3].Position = v[ PosIdx0];
        Vector b = m_pVertices[i * 3 + 1].Position = v[ PosIdx1];
        Vector c = m_pVertices[i * 3 + 2].Position = v[ PosIdx2];
        
        m_pVertices[i * 3].TexcoordS = t[TexIdx0].s;
        m_pVertices[i * 3 + 1].TexcoordS = t[TexIdx1].s;
        m_pVertices[i * 3 + 2].TexcoordS = t[TexIdx2].s;
        
        m_pVertices[i * 3].TexcoordT = t[TexIdx0].t;
        m_pVertices[i * 3 + 1].TexcoordT = t[TexIdx1].t;
        m_pVertices[i * 3 + 2].TexcoordT = t[TexIdx2].t;
        
        Vector normal = (b-a).cross(c-a);
        normal.normalize();
        
        m_pVertices[i * 3].Normal =
        m_pVertices[i * 3 + 1].Normal =
        m_pVertices[i * 3 + 2].Normal = normal;
        
        m_pVertices[i * 3].Material = f[i].material;
    }
    
    inStream.close();
}

const BoundingBox& Model::boundingBox() const
{
    return m_Box;
}

///////////////////////////////////////////////////////////////////////////////
// draw the local axis of an object
///////////////////////////////////////////////////////////////////////////////
void drawAxis(float size)
{
    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
    glDisable(GL_LIGHTING);
    glPushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
    //      the light position when you draw GL_LINES
    //      and GL_POINTS. remember the matrix.
    
    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glEnd();
    glLineWidth(1);
    
    // draw arrows(actually big square dots)
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, size);
    glEnd();
    glPointSize(1);
    
    // restore default settings
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
}

void Model::drawTriangles() const
{
    Material *currentMaterial = NULL;
    
    this->shader->activate();
    
    //std::cout << m_VertexCount << std::endl;
    
    for(unsigned int i = 0; i < m_VertexCount / 3; i++)
    {
        if (this->m_pVertices[i * 3].Material != NULL && currentMaterial != this->m_pVertices[i * 3].Material) {
            currentMaterial = this->m_pVertices[i * 3].Material;
            
            this->shader->setParameter(this->shader->getParameterIdentifier("DiffColor"),
                                       Vector(currentMaterial->getDiffuseColor().R,
                                              currentMaterial->getDiffuseColor().G,
                                              currentMaterial->getDiffuseColor().B));
            this->shader->setParameter(this->shader->getParameterIdentifier("SpecColor"),
                                       Vector(currentMaterial->getSpecularColor().R,
                                              currentMaterial->getSpecularColor().G,
                                              currentMaterial->getSpecularColor().B));
            this->shader->setParameter(this->shader->getParameterIdentifier("AmbientColor"),
                                       Vector(currentMaterial->getAmbientColor().R,
                                              currentMaterial->getAmbientColor().G,
                                              currentMaterial->getAmbientColor().B));
            this->shader->setParameter(this->shader->getParameterIdentifier("SpecExp"), currentMaterial->getSpecularExponent());
            
            if (currentMaterial->getDiffuseTexture().isValid()) { //falls keine diffuse Texture gefunden wird, weiße Textur anwenden, da sonst schwarzes bild
                currentMaterial->getDiffuseTexture().apply();
            } else {
                this->whiteTexture.apply();
            }
            this->shader->setParameter(this->shader->getParameterIdentifier("DiffuseTexture"), 0);
        } else {
            glColor3f(1, 0.6, 0.6);
        }
        
        glBegin(GL_TRIANGLES);
        
        Vertex firstVertex = m_pVertices[i * 3];
        glNormal3f(firstVertex.Normal.X, firstVertex.Normal.Y, firstVertex.Normal.Z);
        glTexCoord2f(firstVertex.TexcoordS * this->tilingU, firstVertex.TexcoordT * this->tilingV);
        glVertex3f(firstVertex.Position.X, firstVertex.Position.Y, firstVertex.Position.Z);
        
        Vertex secondVertex = m_pVertices[i * 3 + 1];
        glNormal3f(secondVertex.Normal.X, secondVertex.Normal.Y, secondVertex.Normal.Z);
        glTexCoord2f(secondVertex.TexcoordS * this->tilingU, secondVertex.TexcoordT * this->tilingV);
        glVertex3f(secondVertex.Position.X, secondVertex.Position.Y, secondVertex.Position.Z);
        
        Vertex thirdVertex = m_pVertices[i * 3 + 2];
        glNormal3f(thirdVertex.Normal.X, thirdVertex.Normal.Y, thirdVertex.Normal.Z);
        glTexCoord2f(thirdVertex.TexcoordS * this->tilingU, thirdVertex.TexcoordT * this->tilingV);
        glVertex3f(thirdVertex.Position.X, thirdVertex.Position.Y, thirdVertex.Position.Z);
        glEnd();
    }
    
    this->shader->deactivate();
    
    
    
    /**/
    drawAxis(4);
    
    
    
}

void Model::loadMaterial(const char* filename, std::map<std::string, int> &materialMap) {
    Material material;
    std::fstream inStream(filename, std::ios::in);
    std::string noun, junk;
    
    if (!inStream) {
        std::cout << "Model::loadMaterial:Cannot open file " << filename << std::endl;
        return;
    }
    
    int maxCharactersPerLine = 8192; // should be enough for obj files
    char inputBuffer[maxCharactersPerLine];
    while (inStream.peek() != -1) {
        inStream.getline(&inputBuffer[0], maxCharactersPerLine);
        
        std::string lineBuffer(&inputBuffer[0]);
        
        // Trim newline '\r\n' or '\n'
        if (lineBuffer.size() > 0) {
            if (lineBuffer[lineBuffer.size() - 1] == '\n') {
                lineBuffer.erase(lineBuffer.size() - 1);
            }
        }
        if (lineBuffer.size() > 0) {
            if (lineBuffer[lineBuffer.size() - 1] == '\r') {
                lineBuffer.erase(lineBuffer.size() - 1);
            }
        }
        
        // Skip if empty line.
        if (lineBuffer.empty()) {
            continue;
        }
        
        const char *token = lineBuffer.c_str();
        
        // skip whitespace and tabs
        token += strspn(token, " \t");
        
        assert(token);
        
        // skip on empty line or comment
        if (token[0] == '\0' || token[0] == '#') {
            continue;
        }
        
        // new material definition
        if (strncmp(token, "newmtl", 6) == 0) {
            if (!material.getName().empty()) {
                // flush previous material
                materialMap.insert(std::pair<std::string, int>(material.getName(), this->m_MaterialCount));
                this->m_pMaterials[this->m_MaterialCount++] = material;
            }
            
            material = Material();
            
            char materialName[4096];
            token += 7;
            sscanf(token, "%s", materialName);
            material.setName(materialName);
            continue;
        }
        
        // ambient
        if (strncmp(token, "Ka", 2) == 0) {
            token += 2;
            Color ambientColor;
            sscanf(token, "%f %f %f", &ambientColor.R, &ambientColor.G, &ambientColor.B);
            material.setAmbientColor(ambientColor);
            continue;
        }
        
        // diffuse
        if (strncmp(token, "Kd", 2) == 0) {
            token += 2;
            Color diffuseColor;
            sscanf(token, "%f %f %f", &diffuseColor.R, &diffuseColor.G, &diffuseColor.B);
            material.setDiffuseColor(diffuseColor);
            continue;
        }
        
        // specular
        if (strncmp(token, "Ks", 2) == 0) {
            token += 2;
            Color specularColor;
            sscanf(token, "%f %f %f", &specularColor.R, &specularColor.G, &specularColor.B);
            material.setSpecularColor(specularColor);
            continue;
        }
        
        // specular exponent
        if (strncmp(token, "Ns", 2) == 0) {
            token += 2;
            float specularExponent = 0.0;
            sscanf(token, "%f", &specularExponent);
            material.setSpecularExponent(specularExponent);
            continue;
        }
        
        // diffuse texture
        if (strncmp(token, "map_Kd", 6) == 0) {
            token += 7;
            std::string filepath(filename);
            filepath = filepath.substr(0, filepath.find_last_of("\\/") + 1);
            
            material.setDiffuseTexture((filepath + std::string(token)).c_str());
            continue;
        }
    }
    
    // flush last material.
    materialMap.insert(std::pair<std::string, int>(material.getName(), this->m_MaterialCount));
    this->m_pMaterials[this->m_MaterialCount++] = material;
}
