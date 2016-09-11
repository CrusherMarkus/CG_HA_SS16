//
//  Vehicle.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vehicle.hpp"

Vehicle::Vehicle() {
}

Vehicle::~Vehicle() {

}

bool Vehicle::load(const char* modelName) {
    
    ModelBuilder modelBuilder;
    
    //sceneObj->setScaling(Vector(0.7,0.7,0.7));
    //sceneObj->setLocalTransform(Vector(0,0,-3), Vector(0,1,0), 0);
    std::cout << "modelName " << modelName << std::endl;
    
    

    
    Model *newModel = modelBuilder.buildModel(modelName);
    sceneObj->setModel(newModel);
   
    sceneObj->setLocalTransform(Vector(), Vector(0, 1, 0), 0);
    sceneObj->setScaling(Vector(0.5, 0.5, 0.5));
    
    sceneObj->computeBoundingBox();
    
    
    return true;
}

void Vehicle::steer(float ForwardBackward, float LeftRight) {

    forwardBackward = ForwardBackward;
    leftRight = LeftRight;
}

void Vehicle::update(float delta){
    
    m_MatrixVehicle = sceneObj->getLocalTransform();
    this->position = m_MatrixVehicle.translation();
    Matrix rm;
    Matrix m;
    
    m.translation(leftRight*3*delta, 0, 0);
    m_MatrixVehicle *= m;
    m.translation(0, 0, forwardBackward*3*delta);
    m_MatrixVehicle *= m;
    
    this->angle += this->leftRight *delta/ 1000;
    
    if(this->angle >= M_PI * 2 || this->angle <= -M_PI * 2)
        this->angle = 0;
    
    if (leftRight == 1){
        this->angle = this->angle +0.1;
        if(this->angle > 360){
            this->angle = 0;
        }
        
        m.translation(this->position.X,this->position.Y,this->position.Z);
        
        rm.rotationY(this->angle);
        m_MatrixVehicle = m*rm;
        
    }else if(leftRight == -1){
        this->angle = this->angle -0.1;
        if(this->angle < 0){
            this->angle= 360;
        }
        rm.rotationY(this->angle);
        m.translation(this->position.X,this->position.Y,this->position.Z);
        m_MatrixVehicle = m*rm;
    }
    //cout << "angle:"<<this->angle << endl;
    
    
    sceneObj->setLocalTransform(m_MatrixVehicle);
    

}

Vector& Vehicle::getPosition(){
    return this->position;
}

void Vehicle::draw() {
    
    Matrix m;
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1.0f,0,0);
    glVertex3f(p.X, p.Y, p.Z);
    glEnd();
    
    glPushMatrix();
    glMultMatrixf(sceneObj->getGlobalTransform() * m.scale(sceneObj->getScaling()));
    sceneObj->getModel()->draw();
    glPopMatrix();
    
}

float Vehicle::getForwardBackward() {
    return forwardBackward;
}
float Vehicle::getLeftRight() {
    return leftRight;
}

