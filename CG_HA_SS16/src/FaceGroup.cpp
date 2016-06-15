//
//  FaceGroup.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "FaceGroup.hpp"

FaceGroup::FaceGroup() {
    this->whiteTexture.LoadFromBMP("shader/white.bmp");
}

void FaceGroup::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferIdentififer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, Position.X));
    
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, Normal.X));
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, TexcoordS));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferIdentifier);
    glDrawElements(GL_TRIANGLES, this->numberOfIndices, GL_UNSIGNED_INT, 0);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}