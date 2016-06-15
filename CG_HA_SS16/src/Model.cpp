//
//  Model.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
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

Model::Model(const std::string &name) {
    this->name = name;
    this->materials = NULL;
    this->materialCount = 0;
    this->selected = false;
    
    this->whiteTexture.LoadFromBMP("shader/white.bmp");
}

Model::~Model() {
    //delete [] this->materials;
}

#pragma mark - Getter/Setter

std::string &Model::getName() {
    return this->name;
}

std::vector<Vertex> &Model::getVertices() {
    return this->vertices;
}

void Model::setVertices(std::vector<Vertex> &vertices) {
    this->vertices = vertices;
}

void Model::setMaterials(Material *materials, int materialCount) {
    this->materials = materials;
    this->materialCount = materialCount;
}

const BoundingBox &Model::getBoundingBox() {
    return this->boundingBox;
}

void Model::setBoundingBox(const BoundingBox &boundingBox) {
    this->boundingBox = boundingBox;
}

bool Model::isSelected() const {
    return this->selected;
}

void Model::setSelected(bool isSelected) {
    this->selected = isSelected;
}

#pragma mark - Public methods

void Model::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferIdentififer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, Position.X));
    
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, Normal.X));
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, TexcoordS));
    
    ShaderProgram *shader;
    shader->activate();
    if (this->materialCount > 0) {
        Material *mat = &this->materials[0];
        shader->setParameter(shader->getParameterIdentifier("DiffColor"), Vector(
                                                                                 mat->getDiffuseColor().R,
                                                                                 mat->getDiffuseColor().G,
                                                                                 mat->getDiffuseColor().B
                                                                                 ));
        shader->setParameter(shader->getParameterIdentifier("SpecColor"), Vector(
                                                                                 mat->getSpecularColor().R,
                                                                                 mat->getSpecularColor().G,
                                                                                 mat->getSpecularColor().B
                                                                                 ));
        shader->setParameter(shader->getParameterIdentifier("AmbientColor"), Vector(
                                                                                    mat->getAmbientColor().R,
                                                                                    mat->getAmbientColor().G,
                                                                                    mat->getAmbientColor().B
                                                                                    ));
        shader->setParameter(shader->getParameterIdentifier("SpecExp"), mat->getSpecularExponent());
        
        if (mat->getDiffuseTexture().isValid()) {
            mat->getDiffuseTexture().apply();
        } else {
            this->whiteTexture.apply();
        }
        shader->setParameter(shader->getParameterIdentifier("DiffuseTexture"), 0);
    }
    shader->setParameter(shader->getParameterIdentifier("highlighted"), this->isSelected());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferIdentifier);
    glDrawElements(GL_TRIANGLES, this->numberOfIndices, GL_UNSIGNED_INT, 0);
    shader->deactivate();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
