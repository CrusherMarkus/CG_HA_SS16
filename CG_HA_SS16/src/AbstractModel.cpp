//
//  AbstractModel.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "AbstractModel.hpp"

AbstractModel::AbstractModel() {
    this->numberOfVertices = 0;
    this->numberOfIndices = 0;
    
    glGenBuffers(1, &this->vertexBufferIdentififer);
    glGenBuffers(1, &this->indexBufferIdentifier);
}

AbstractModel::~AbstractModel() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->vertexBufferIdentififer);
    glDeleteBuffers(1, &this->indexBufferIdentifier);
}