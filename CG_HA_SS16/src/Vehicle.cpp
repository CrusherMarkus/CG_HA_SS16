//
//  Vehicle.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vehicle.hpp"

Vehicle::Vehicle() {
    m_MatrixVehicle = m_MatrixVehicle.identity();
}

Vehicle::~Vehicle() {

}

bool Vehicle::load(const char* Model, const Vector& StartPos,
                const char* vertexShader, const char* fragmentShader) {
    
    
    ModelBuilder modelBuilder;
    
    model = modelBuilder.buildModel("hallo", Model);

    
    Matrix m;
    m.translation(StartPos);
    
    m_MatrixVehicle *=m;
    position = StartPos;
    
    return true;
}

void Vehicle::steer(float ForwardBackward, float LeftRight) {
    cout << "ForwardBackward: " << ForwardBackward << endl;
    cout << "LeftRight: " << LeftRight << endl;
    forwardBackward = ForwardBackward;
    leftRight = LeftRight;
}



void Vehicle::update(float delta){
    
    this->position = m_MatrixVehicle.translation();
    /*
    cout << "m_MatrixVehicle.translation().X:" << m_MatrixVehicle.translation().X << endl;
    cout << "m_MatrixVehicle.translation().Y:" << m_MatrixVehicle.translation().Y << endl;
    cout << "m_MatrixVehicle.translation().Z:" << m_MatrixVehicle.translation().Z << endl;
    cout << "this->position.X:" << this->position.X << endl;
    cout << "this->position.Y:" << this->position.Y << endl;
    cout << "this->position.Z:" << this->position.Z << endl;*/
    
    Matrix m;
    
    if((m_MatrixVehicle.translation().Z>=0 && forwardBackward == 1) || (m_MatrixVehicle.translation().Z<=-3 && forwardBackward ==-1)){
        cout << "Z-Grenze erreicht!" << endl;
        
    }else{
        m.translation(0,0,forwardBackward*3*delta);
        m_MatrixVehicle *= m;
    }
    
    if((m_MatrixVehicle.translation().X>3 && leftRight == 1) || (m_MatrixVehicle.translation().X<=-3 && leftRight ==-1)){
        cout << "X-Grenze erreicht!" << endl;
        
    }else{
        m.translation(leftRight*3*delta, 0,0);
        m_MatrixVehicle *= m;
    }
}

Vector& Vehicle::getPosition(){
    return this->position;
}

void Vehicle::draw() {
    Matrix m = m_MatrixVehicle;
        
    
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1.0f,0,0);
    glVertex3f(p.X, p.Y, p.Z);
    glEnd();
    glPushMatrix();
    glMultMatrixf(m);
    model->draw();
    glPopMatrix();
}