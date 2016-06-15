//
//  ObjParser.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "ObjParser.hpp"

ObjParser::ObjParser() {
    this->reset();
}

ObjParser::~ObjParser() {
    
}

ObjModel *ObjParser::loadModelFromFile(const std::string &pathAndFilename) {
    this->reset();
    
    std::ifstream inStream(pathAndFilename);
    if (!inStream) {
        std::cout << "Cannot open file " << pathAndFilename << std::endl;
        exit(-1);
    }
    
    boost::filesystem::path p(pathAndFilename);
    this->currentWorkingDirectory = p.parent_path();
    
    std::vector<Vector> v;
    std::vector<TextureCoordinate> t;
    std::vector<Face> f;
    
    std::map<std::string, unsigned int> materialMap;
    unsigned int currentMaterialIdentifier = 0;
    
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
            TextureCoordinate tc;
            sscanf(token, "%f %f", &tc.s, &tc.t );
            t.push_back(tc);
            continue;
        }
        
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
            face.materialIdentifier = currentMaterialIdentifier;
            f.push_back(face);
            
            if (matches == 8) {
                face2.pidx[0] = vertexIndex[2];
                face2.pidx[1] = vertexIndex[3];
                face2.pidx[2] = vertexIndex[0];
                face2.tidx[0] = texIndex[2];
                face2.tidx[1] = texIndex[3];
                face2.tidx[2] = texIndex[0];
                face.materialIdentifier = currentMaterialIdentifier;
                f.push_back(face2);
            }
            
            continue;
        }
        
        // mtllib
        if (strncmp(token, "mtllib", 6) == 0) {
            char materialFile[256];
            token += 7;
            sscanf(token, "%s", materialFile);
            this->loadMaterial(materialFile, materialMap);
        }
        
        // use mtl
        if (strncmp(token, "usemtl", 6) == 0) {
            char materialName[256];
            token += 7;
            sscanf(token, "%s", materialName);
            std::map<std::string, unsigned int>::iterator materialIterator = materialMap.find(std::string(materialName));
            if (materialIterator != materialMap.end()) {
                currentMaterialIdentifier = materialIterator->second;
            }
        }
    }
    
    inStream.close();
    
    ObjModel *model = new ObjModel();
    model->positions = v;
    model->textureCoordinates = t;
    model->faces = f;
    model->materials = this->materials;
    model->materialCount = this->materialCount;
    
    return model;
}

void ObjParser::reset() {
    this->materials = new Material[30];
    this->materialCount = 0;
}

void ObjParser::loadMaterial(const char *materialPathAndFilename, std::map<std::string, unsigned int> &materialMap) {
    const char *absoluteMaterialPathAndFilename = (this->currentWorkingDirectory / materialPathAndFilename).c_str();
    Material material;
    std::fstream inStream(absoluteMaterialPathAndFilename, std::ios::in);
    std::string noun, junk;
    
    if (!inStream) {
        std::cout << "Cannot open file " << materialPathAndFilename << std::endl;
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
                materialMap.insert(std::pair<std::string, int>(material.getName(), this->materialCount));
                this->materials[this->materialCount++] = material;
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
            const char *absoluteTexturePathAndFilename = (this->currentWorkingDirectory / token).c_str();
            material.setDiffuseTexture(absoluteTexturePathAndFilename);
            continue;
        }
    }
    
    // flush last material.
    materialMap.insert(std::pair<std::string, int>(material.getName(), this->materialCount));
    this->materials[this->materialCount++] = material;
}