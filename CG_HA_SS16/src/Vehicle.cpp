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

bool Vehicle::load(const char* Model, const char* vertexShader, const char* fragmentShader) {
    
    

    
    sceneObj.setScaling(Vector(0.7,0.7,0.7));
    sceneObj.setLocalTransform(Vector(0,0,-3), Vector(0,1,0), 0);
    model = sceneObj.loadModel(Model, false, vertexShader, fragmentShader);
    position = Vector (0,0,-3);
    
    
    
    return true;
}

void Vehicle::steer(float ForwardBackward, float LeftRight) {

    forwardBackward = ForwardBackward;
    leftRight = LeftRight;
}

void Vehicle::update(float delta){
    
    m_MatrixVehicle = sceneObj.getLocalTransform();
    this->position = m_MatrixVehicle.translation();
    
    
    // Begrenzung links/rechts
    if((m_MatrixVehicle.translation().X > 3 && leftRight == 1) || (m_MatrixVehicle.translation().X < -3 && leftRight == -1)){
        cout << "X-Grenze erreicht!" << endl;
    } else {
        Matrix m;
        m.translation(leftRight*3*delta, 0, 0);
        m_MatrixVehicle *= m;
        m.translation(0, 0, forwardBackward*3*delta);
        m_MatrixVehicle *= m;
    }
    
    Matrix MH, RM, RTM;
    
    sceneObj.setLocalTransform(m_MatrixVehicle);
    

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
    glMultMatrixf(sceneObj.getLocalTransform() * m.scale(sceneObj.getScaling()));
    model.drawTriangles();
    glPopMatrix();
    
}

float Vehicle::getForwardBackward() {
    return forwardBackward;
}
float Vehicle::getLeftRight() {
    return leftRight;
}

