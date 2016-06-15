//
//  ModelBuilder.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
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

#pragma mark - Public methods

Model *ModelBuilder::buildModel(const std::string &name, const std::string &modelPathAndFilename) {
    ObjModel *objModel;
    if (this->cachedObjModels.count(name) != 0) {
        objModel = this->cachedObjModels[name];
    } else {
        ObjParser objParser;
        objModel = objParser.loadModelFromFile(modelPathAndFilename);
        this->cachedObjModels.insert(std::pair<std::string, ObjModel *>(name, objModel));
    }
    
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
        
        Vector a = vertices[i * 3].Position = objModel->positions[PosIdx0];
        Vector b = vertices[i * 3 + 1].Position = objModel->positions[PosIdx1];
        Vector c = vertices[i * 3 + 2].Position = objModel->positions[PosIdx2];
        
        vertices[i * 3].TexcoordS = objModel->textureCoordinates[TexIdx0].s;
        vertices[i * 3 + 1].TexcoordS = objModel->textureCoordinates[TexIdx1].s;
        vertices[i * 3 + 2].TexcoordS = objModel->textureCoordinates[TexIdx2].s;
        
        vertices[i * 3].TexcoordT = objModel->textureCoordinates[TexIdx0].t;
        vertices[i * 3 + 1].TexcoordT = objModel->textureCoordinates[TexIdx1].t;
        vertices[i * 3 + 2].TexcoordT = objModel->textureCoordinates[TexIdx2].t;
        
        Vector normal = (b - a).cross(c - a);
        normal.normalize();
        
        vertices[i * 3].Normal =
        vertices[i * 3 + 1].Normal =
        vertices[i * 3 + 2].Normal = normal;
        
        indices[i * 3] = i * 3;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 2;
    }
    for (unsigned int i = 0; i < numberOfVertices; i++) {
        vertices[i].Normal.normalize();
    }
    
    Model *newModel = new Model(name);
    newModel->setMaterials(objModel->materials, objModel->materialCount);
    newModel->setVertices(vertices);
    newModel->uploadVerticesToBuffer<Vertex>((unsigned int)vertices.size(), &vertices[0]);
    newModel->uploadIndicesToBuffer<unsigned int>((unsigned int)indices.size(), &indices[0]);
    
    return newModel;
}