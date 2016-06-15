//
//  Vehicle.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vehicle.hpp"

Vehicle::~Vehicle() {
}

bool Vehicle::load(const char* Model, const Vector& StartPos,
                const char* vertexShader, const char* fragmentShader) {
    this->position = StartPos;
    
    if(!this->model.load(Model, false, vertexShader, fragmentShader))
        return false;
    
    return true;
}

void Vehicle::steer(float ForwardBackward, float LeftRight) {
    this->speed = ForwardBackward;
    this->rotation = LeftRight;
}

const Matrix& Vehicle::getModelViewMatrix() const{
    return m_VehicleMatrix;
}

void Vehicle::update(float delta){

    position = getPosition(); //Get Updated position
    
    Matrix TM;
    TM.identity();
    Matrix RM;
    RM.identity();
    
    
    TM.translation(position);
    RM.rotationY(heading);
    m_VehicleMatrix = TM*RM;

}

void Vehicle::draw() {
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(m_VehicleMatrix);
    model.drawTriangles();
    glPopMatrix();
}

void Vehicle::setPosition(const Vector & position)
{
    this->position = position;
}

const Vector & Vehicle::getPosition() const
{
    return position;
}

