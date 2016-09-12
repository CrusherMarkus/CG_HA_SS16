//
//  Terrain.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Terrain.hpp"
#include <stdio.h>
#include "Terrain.hpp"
#include "Texture.hpp"
#include "RgbImage.hpp"
#include "ShaderManager.hpp"
#include "ShaderProgram.hpp"

Terrain::Terrain() {
    
}

Terrain::~Terrain() {
    
}

std::vector<TerrainVertex> &Terrain::getVertices() {
    return this->vertices;
}

void Terrain::setVertices(std::vector<TerrainVertex> &vertices) {
    this->vertices = vertices;
}

std::vector<unsigned int> &Terrain::getIndices() {
    return this->indices;
}

void Terrain::setIndices(std::vector<unsigned int> &indices) {
    this->indices = indices;
}

const Vector &Terrain::getDimensions() const {
    return this->dimensions;
}

void Terrain::setDimensions(const Vector &dimensions) {
    this->dimensions = dimensions;
}

Texture &Terrain::getDetailMap1() {
    return this->detailMap1;
}

Texture &Terrain::getDetailMap2() {
    return this->detailMap2;
}

Texture &Terrain::getMixMap() {
    return this->mixMap;
}

unsigned int Terrain::getHeightMapImageWidth() {
    return this->heightMapImageWidth;
}

void Terrain::setHeightMapImageWidth(unsigned int heightMapImageWidth) {
    this->heightMapImageWidth = heightMapImageWidth;
}

unsigned int Terrain::getHeightMapImageHeight() {
    return this->heightMapImageHeight;
}

void Terrain::setHeightMapImageHeight(unsigned int heightMapImageHeight) {
    this->heightMapImageHeight = heightMapImageHeight;
}

void Terrain::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferIdentififer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(TerrainVertex), (void *)offsetof(TerrainVertex, Pos.X));
    
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(TerrainVertex), (void *)offsetof(TerrainVertex, Normal.X));
    
    // apply grass texture
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(TerrainVertex), (void *)offsetof(TerrainVertex, u1));
    this->detailMap1.apply();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    // apply sand texture
    glActiveTexture(GL_TEXTURE1);
    glClientActiveTexture(GL_TEXTURE1);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(TerrainVertex), (void *)offsetof(TerrainVertex, u1));
    this->detailMap2.apply();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    // apply mixmap
    glActiveTexture(GL_TEXTURE2);
    glClientActiveTexture(GL_TEXTURE2);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(TerrainVertex), (void *)offsetof(TerrainVertex, u0));
    this->mixMap.apply();
    
    // initailize shader and draw the triangles
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferIdentifier);
    /*ShaderProgram *shader = ShaderManager::getInstance().getShader("terrain");
     
     shader->activate();
     shader->setParameter(shader->getParameterIdentifier("DetailMap1"), 1);
     shader->setParameter(shader->getParameterIdentifier("DetailMap2"), 0);
     shader->setParameter(shader->getParameterIdentifier("MixMap"), 2);
     
     glDrawElements(GL_TRIANGLES, this->numberOfIndices, GL_UNSIGNED_INT, 0);
     shader->deactivate();*/
    
    // disable mixmap
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
    // disable sand texture
    glActiveTexture(GL_TEXTURE1);
    glClientActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
    // disable gras texture and set modulate as default behaviour for unit 0
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDisable(GL_TEXTURE_2D);
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Terrain::bindTextures() {
    
}

void Terrain::unbindTextures() {
    
}