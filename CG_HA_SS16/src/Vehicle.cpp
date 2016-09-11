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

bool Vehicle::load(const char* ChassisModel, const char* CanonModel, const Vector& StartPos){
    ModelBuilder modelBuilder;
    
    std::cout << "ChassisModel " << ChassisModel << std::endl;
    std::cout << "CanonModel " << CanonModel << std::endl;
    
    
    Model *chassisModel = modelBuilder.buildModel(ChassisModel);
    sceneObjChassisModel->setModel(chassisModel);
    sceneObjChassisModel->setScaling(Vector(0.5, 0.5, 0.5));
    
    Model *canonModel = modelBuilder.buildModel(CanonModel);
    sceneObjCanonModel->setModel(canonModel);
    sceneObjCanonModel->setScaling(Vector(0.5, 0.5, 0.5));
    
    
	this->position = StartPos;
    sceneObjChassisModel->computeBoundingBox();
    
    return true;
}

void Vehicle::steer(float ForwardBackward, float LeftRight) {
    this->forwardBackward = ForwardBackward;
    this->leftRight = LeftRight;
}

void Vehicle::update(float delta){
    
    
    // Chassis
    m_MatrixVehicle = sceneObjChassisModel->getLocalTransform();
    
    
    Matrix TM;
    TM.identity();
    Matrix RM;
    RM.identity();
    Matrix RTM, MH;
    
    static float distanceX = 0;
    static float distanceZ = 0;
    static float ang = 0;
    
    // Kurve
    ang += this->leftRight * delta;
    RM.rotationY(ang);
    
    // Vorne und zurück
    distanceX += this->forwardBackward * RM.right().X * delta;
    distanceZ += this->forwardBackward * RM.right().Z  * delta;
    
    //std::cout << "distanceX " << distanceX << std::endl;
    //std::cout << "distanceZ " << distanceZ << std::endl;
    
    TM.translation(distanceX, 0, distanceZ);
    
    // Translationmatrix * Rotationsmatrix
    RTM = TM * RM;
    
    m_MatrixVehicle = RTM;

    // Chassis und Cannon gleiche Position
    sceneObjChassisModel->setLocalTransform(m_MatrixVehicle);
    sceneObjCanonModel->setLocalTransform(m_MatrixVehicle);
    this->position = m_MatrixVehicle.translation();
    sceneObjChassisModel->computeBoundingBox();
}

void Vehicle::updateProjektils(float deltaTimeInSeconds){
    
    // Projektile
    for (list<Projektil*>::const_iterator it = (projektils).begin(); it != (projektils).end();)
    {
        (**it).draw(deltaTimeInSeconds);
        
        /*
         cout << "(**it).getPosition().length()" << (**it).getPosition().length() << endl;
         cout << "(**it).getMaxDistance()" << (**it).getMaxDistance() << endl;
         */
        
        if((**it).getPosition().length() >= (**it).getMaxDistance()) {
            projektils.pop_front();
        }
        ++it;
    }

}



Vector& Vehicle::getPosition(){
    return this->position;
}

void Vehicle::draw() {
    BoundingBox lol = sceneObjChassisModel->getModel()->getBoundingBox();
    drawBB(lol);
    Matrix m;
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1.0f,0,0);
    glVertex3f(p.X, p.Y, p.Z);
    glEnd();
    
    glPushMatrix();
    glMultMatrixf(sceneObjChassisModel->getLocalTransform() * m.scale(sceneObjChassisModel->getScaling()));
    sceneObjChassisModel->getModel()->draw();
    glPopMatrix();
    
    glPushMatrix();
    glMultMatrixf(sceneObjCanonModel->getLocalTransform() * m.scale(sceneObjCanonModel->getScaling()));
    sceneObjCanonModel->getModel()->draw();
    glPopMatrix();
    
}

float Vehicle::getForwardBackward() {
    return this->forwardBackward;
}
float Vehicle::getLeftRight() {
    return this->leftRight;
}

list<Projektil*> Vehicle::getProjektils() {
    return projektils;
}

void Vehicle::spawnProjektil()
{
    
    // Startposition des Projektils
    Vector projektilPosition = *new Vector(this->position.X, this->position.Y+1.1, this->position.Z+2.1);
    
    
    //cout << "rotationAxis.X:"<< rotationAxis.X << endl;
    //cout << "rotationAxis.Y:"<< rotationAxis.Y << endl;
    //cout << "rotationAxis.Z:"<< rotationAxis.Z << endl;
    
    // Richtung der Z-Achse
    Matrix direction = this->sceneObjCanonModel->getLocalTransform();
    Vector directionZ = direction.right();
    cout << "x: "<< directionZ.X << "y: " <<directionZ.Y<<"z: "<<directionZ.Z << endl;
   // directionZ = *new Vector(this->position.X, this->position.Y, this->position.Z+1);
    directionZ.normalize();
    //projektilPosition.Z += direction.Z;
    
    

    
    
    //if(projektils.size() < 5) {
        projektils.push_back(new Projektil(this->position, directionZ));
    //}
}

void Vehicle::drawBB(BoundingBox &b){
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(b.getMax().X,b.getMax().Y,b.getMin().Z);
    glVertex3f(b.getMin().X,b.getMax().Y,b.getMin().Z);
    glVertex3f(b.getMin().X,b.getMin().Y,b.getMin().Z);
    glVertex3f(b.getMax().X,b.getMin().Y,b.getMin().Z);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(b.getMax().X,b.getMin().Y,b.getMax().Z);
    glVertex3f(b.getMax().X,b.getMax().Y,b.getMax().Z);
    glVertex3f(b.getMin().X,b.getMax().Y,b.getMax().Z);
    glVertex3f(b.getMin().X,b.getMin().Y,b.getMax().Z);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(b.getMax().X,b.getMax().Y,b.getMin().Z);
    glVertex3f(b.getMax().X,b.getMax().Y,b.getMax().Z);
    glVertex3f(b.getMin().X,b.getMax().Y,b.getMax().Z);
    glVertex3f(b.getMin().X,b.getMax().Y,b.getMin().Z);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(b.getMax().X,b.getMin().Y,b.getMax().Z);
    glVertex3f(b.getMin().X,b.getMin().Y,b.getMax().Z);
    glVertex3f(b.getMin().X,b.getMin().Y,b.getMin().Z);
    glVertex3f(b.getMax().X,b.getMin().Y,b.getMin().Z);
    glEnd();
}