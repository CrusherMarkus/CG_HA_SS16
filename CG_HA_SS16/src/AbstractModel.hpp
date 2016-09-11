//
//  AbstractModel.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef AbstractModel_hpp
#define AbstractModel_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>

class AbstractModel {
protected:
    unsigned int numberOfVertices;
    unsigned int numberOfIndices;
    GLuint vertexBufferIdentififer;
    GLuint indexBufferIdentifier;
    
public:
    AbstractModel();
    virtual ~AbstractModel();
    
    template<class T> void uploadVerticesToBuffer(unsigned int numberOfVertices, T *vertices) {
        this->numberOfVertices = numberOfVertices;
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferIdentififer);
        glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(T), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    template<class T> void updateBufferedVertices(unsigned int offset, unsigned int numberOfVertices, T *vertices) {
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferIdentififer);
        glBufferSubData(GL_ARRAY_BUFFER, offset, numberOfVertices * sizeof(T), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    template<class T> void uploadIndicesToBuffer(unsigned int numberOfIndices, T *indices) {
        this->numberOfIndices = numberOfIndices;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferIdentifier);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(T), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    virtual void draw() const = 0;
};


#endif /* AbstractModel_hpp */
