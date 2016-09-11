//
//  ModelBuilder.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "ModelBuilder.hpp"

ModelBuilder::ModelBuilder() {
    
}

ModelBuilder::~ModelBuilder() {
    for (auto &it : this->cachedObjModels) {
        delete it.second;
    }
    this->cachedObjModels.clear();
}

Model *ModelBuilder::buildModel(const char* Filename) {
    ObjModel *objModel;
    ObjParser objParser;
    std::cout << "Filename " << Filename << std::endl;
    objModel = objParser.loadModelFromFile(Filename);
    
    // assemble vertices and materials from collected data
    unsigned int numberOfFaces = (int)objModel->faces.size();
    unsigned int numberOfVertices = numberOfFaces * 3;
    std::vector<Vertex> vertices(numberOfVertices);
    std::vector<unsigned int> indices(numberOfVertices);
    FaceGroup currentFaceGroup;
    for(int i = 0; i < numberOfFaces; i++) {
        // @todo: check for different mats and create face groups
        
        unsigned int PosIdx0 = objModel->faces[i].pidx[0] - 1;
        unsigned int PosIdx1 = objModel->faces[i].pidx[1] - 1;
        unsigned int PosIdx2 = objModel->faces[i].pidx[2] - 1;
        
        unsigned int TexIdx0 = objModel->faces[i].tidx[0] - 1;
        unsigned int TexIdx1 = objModel->faces[i].tidx[1] - 1;
        unsigned int TexIdx2 = objModel->faces[i].tidx[2] - 1;
        
        // Positionen der Vertices setzen
        Vector a = vertices[i * 3].position = objModel->positions[PosIdx0];
        Vector b = vertices[i * 3 + 1].position = objModel->positions[PosIdx1];
        Vector c = vertices[i * 3 + 2].position = objModel->positions[PosIdx2];
        
        // Wenn aktuelles Objekt Textkoordinaten enthaelt, eben diese setzen
        vertices[i * 3].texCoordS = objModel->textureCoordinates[TexIdx0].s;
        vertices[i * 3 + 1].texCoordS = objModel->textureCoordinates[TexIdx1].s;
        vertices[i * 3 + 2].texCoordS = objModel->textureCoordinates[TexIdx2].s;
        
        vertices[i * 3].texCoordT = objModel->textureCoordinates[TexIdx0].t;
        vertices[i * 3 + 1].texCoordT = objModel->textureCoordinates[TexIdx1].t;
        vertices[i * 3 + 2].texCoordT = objModel->textureCoordinates[TexIdx2].t;
        
        // Normalen berechnen

        Vector normal = (b - a).cross(c - a);
        normal.normalize();
        
        vertices[i * 3].normal =
        vertices[i * 3 + 1].normal =
        vertices[i * 3 + 2].normal = normal;
        
        indices[i * 3] = i * 3;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 2;
    }
    for (unsigned int i = 0; i < numberOfVertices; i++) {
        vertices[i].normal.normalize();
    }
    
    Model *newModel = new Model();
    newModel->setMaterials(objModel->materials, objModel->materialCount);
    newModel->setVertices(vertices);
    newModel->uploadVerticesToBuffer<Vertex>((unsigned int)vertices.size(), &vertices[0]);
    newModel->uploadIndicesToBuffer<unsigned int>((unsigned int)indices.size(), &indices[0]);
    
    return newModel;
}

Terrain *ModelBuilder::buildTerrain(const char *heightMap, const char *detailMap1, const char *detailMap2, const char *mixMap, float width, float depth, float heightMultiplier) {
    Terrain *terrain = new Terrain();
    terrain->setDimensions(Vector(width, depth, heightMultiplier));
    
    Texture heightMapTexture;
    // @todo: Raise exceptions
    if (!heightMapTexture.LoadFromBMP(heightMap)) {
        std::cout << "Could not load height map " << heightMap << std::endl;
    }
    
    if (!terrain->getDetailMap1().LoadFromBMP(detailMap1)) {
        std::cout << "Could not load detail map 1 " << detailMap1 << std::endl;
    }
    
    if (!terrain->getDetailMap2().LoadFromBMP(detailMap2)) {
        std::cout << "Could not load detail map 2 " << detailMap2 << std::endl;
    }
    
    if (!terrain->getMixMap().LoadFromBMP(mixMap)) {
        std::cout << "Could not load mix map " << mixMap << std::endl;
    }
    
    const RGBImage *heightMapImage = heightMapTexture.getRGBImage();
    //heightMapImage->saveToDisk("/tmp/heightmap.bmp");
    unsigned int heightMapImageWidth = heightMapImage->getWidth();
    unsigned int heightMapImageHeight = heightMapImage->getHeight();
    terrain->setHeightMapImageWidth(heightMapImageWidth);
    terrain->setHeightMapImageHeight(heightMapImageHeight);
    unsigned int numberOfVertices = heightMapImageWidth * heightMapImageHeight;
    std::vector<TerrainVertex> vertices(numberOfVertices);
    
    // generate vertices from height map
    unsigned int k = width;
    for (unsigned int y = 0; y < heightMapImageHeight; y++)  {
        for (unsigned int x = 0; x < heightMapImageWidth; x++) {
            TerrainVertex vertex;
            
            float flX = (float)x / (heightMapImageWidth - 1) * width - width / 2.f;
            float flZ = (float)y / (heightMapImageHeight - 1) * depth - depth / 2.f;
            
            vertex.u0 = (float)x / (heightMapImageWidth - 1);
            vertex.v0 = (float)y / (heightMapImageHeight - 1);
            vertex.u1 = vertex.u0 * k;
            vertex.v1 = vertex.v0 * k;
            
            Color color = heightMapImage->getPixelColor(x, y);
            vertex.Pos = Vector(-flX, color.R * heightMultiplier, flZ);
            vertex.Normal = Vector();
            
            vertices[x + y * heightMapImageWidth] = vertex;
        }
    }
    
    // indices and normals
    unsigned numberOfIndices = (heightMapImageWidth - 1) * (heightMapImageHeight - 1) * 6;
    std::vector<unsigned int> indices(numberOfIndices);
    unsigned int indexCounter = 0;
    for (unsigned int y = 0; y < heightMapImageHeight - 1; y++)  {
        for (unsigned int x = 0; x < heightMapImageWidth - 1; x++) {
            Vector normal, a, b ,c;
            
            // first triangle - top left, buttom right, top right
            indices[indexCounter++] = x + y * heightMapImageWidth;
            indices[indexCounter++] = (x + 1) + y * heightMapImageWidth;
            indices[indexCounter++] = (x + 1) + (y + 1) * heightMapImageWidth;
            
            a = vertices[indices[indexCounter - 3]].Pos;
            b = vertices[indices[indexCounter - 2]].Pos;
            c = vertices[indices[indexCounter - 1]].Pos;
            normal = (b - a).cross(c - a).normalize();
            
            vertices[indices[indexCounter - 1]].Normal += normal;
            vertices[indices[indexCounter - 2]].Normal += normal;
            vertices[indices[indexCounter - 3]].Normal += normal;
            
            // second triangle - buttom right, top left, buttom right
            indices[indexCounter++] = (x + 1) + (y + 1) * heightMapImageWidth;
            indices[indexCounter++] = x + (y + 1) * heightMapImageWidth;
            indices[indexCounter++] = x + y * heightMapImageWidth;
            
            a = vertices[indices[indexCounter - 3]].Pos;
            b = vertices[indices[indexCounter - 2]].Pos;
            c = vertices[indices[indexCounter - 1]].Pos;
            normal = (b - a).cross(c - a).normalize();
            
            vertices[indices[indexCounter - 1]].Normal += normal;
            vertices[indices[indexCounter - 2]].Normal += normal;
            vertices[indices[indexCounter - 3]].Normal += normal;
        }
    }
    for (unsigned int i = 0; i < numberOfVertices; i++) {
        vertices[i].Normal.normalize();
    }
    
    terrain->setVertices(vertices);
    terrain->uploadVerticesToBuffer<TerrainVertex>((unsigned int)vertices.size(), &vertices[0]);
    terrain->setIndices(indices);
    terrain->uploadIndicesToBuffer<unsigned int>((unsigned int)indices.size(), &indices[0]);
    
    return terrain;
}