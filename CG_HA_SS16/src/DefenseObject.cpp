//
//  DefenseObject.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "DefenseObject.hpp"


DefenseObject::DefenseObject() {
}

DefenseObject::~DefenseObject() {
    
}

bool DefenseObject::load(const char* modelname, const Vector& StartPos) {
    
    ModelBuilder modelBuilder;
    Model *newModel = modelBuilder.buildModel(modelname);
    
    defenseObject->setModel(newModel);
    defenseObject->setLocalTransform(StartPos, *new Vector(0,1,0),0);
    defenseObject->setScaling(Vector(0.5, 0.5, 0.5));
    
    this->position = StartPos;
    return true;
}

void DefenseObject::update(float delta){
    this->m_MatrixDefenseObject = defenseObject->getLocalTransform();
}

void DefenseObject::draw(){
    
    Matrix m;
    glPushMatrix();
    glMultMatrixf(defenseObject->getLocalTransform() * m.scale(defenseObject->getScaling()));
    defenseObject->getModel()->draw();
    glPopMatrix();
}
