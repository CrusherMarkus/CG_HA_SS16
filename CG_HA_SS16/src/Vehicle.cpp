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
    
    std::cout << "ChassisModel:" << ChassisModel << std::endl;
    std::cout << "CanonModel:" << CanonModel << std::endl;
    
    
    Model *chassisModel = modelBuilder.buildModel(ChassisModel);
    sceneObjChassisModel->setModel(chassisModel);
    sceneObjChassisModel->setLocalTransform(StartPos,*new Vector(0,1,0),0);
    sceneObjChassisModel->setScaling(Vector(0.5, 0.5, 0.5));
 
    Model *canonModel = modelBuilder.buildModel(CanonModel);
    sceneObjCanonModel->setModel(canonModel);
    sceneObjCanonModel->setLocalTransform(StartPos,*new Vector(0,1,0),0);
    sceneObjCanonModel->setScaling(Vector(0.5, 0.5, 0.5));
    
    
    
	this->position = StartPos;
    sceneObjChassisModel->computeBoundingBox();

    this->bb = sceneObjChassisModel->getModel()->getBoundingBox();
       
    return true;
}

void Vehicle::steer(float ForwardBackward, float LeftRight) {
    this->forwardBackward = ForwardBackward;
    this->leftRight = LeftRight;
}

const Matrix& Vehicle::getModelViewMatrix() const{
    return m_MatrixVehicle;
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
    
    TM.translation(distanceX, 0, distanceZ);
    
    // Translationmatrix * Rotationsmatrix
    RTM = TM * RM;
    
    m_MatrixVehicle = RTM;

    // Chassis und Cannon gleiche Position
    sceneObjChassisModel->setLocalTransform(m_MatrixVehicle);
    sceneObjCanonModel->setLocalTransform(m_MatrixVehicle);
    this->position = m_MatrixVehicle.translation();
    //sceneObjChassisModel->computeBoundingBox();
    
    
   /* newBB.setMax(*new Vector(m_MatrixVehicle.translation().X+bb.getMax().X,m_MatrixVehicle.translation().Y+bb.getMax().Y,m_MatrixVehicle.translation().Z+bb.getMax().Z));
    newBB.setMin(*new Vector(m_MatrixVehicle.translation().X+bb.getMax().X,m_MatrixVehicle.translation().Y+bb.getMax().Y,m_MatrixVehicle.translation().Z+bb.getMax().Z));*/
    newBB.setMax(bb.getMax()+m_MatrixVehicle.translation());
    newBB.setMin(bb.getMin()+m_MatrixVehicle.translation());
}

void Vehicle::updateProjektils(float deltaTimeInSeconds){
    
    /*
    for (list<Projektil*>::const_iterator it = projektils.begin(); it != projektils.end();)
    {

        (**it).draw(deltaTimeInSeconds);
        cout << "(**it).getPosition().length()" << (**it).getPosition().length() << endl;
        cout << "(**it).getMaxDistance()" << (**it).getMaxDistance() << endl;
   
        
                if((**it).getPosition().length() >= (**it).getMaxDistance()) {
           
            Vector tmp = Vector((*it)->getPosition().X,(*it)->getPosition().Y,(*it)->getPosition().Z);
            this->explosions.push_back(new Explosion(tmp));
            ++it;
            
            this->projektils.erase(this->projektils.begin());
        
        }
    }*/
    // Projektile darstellen
    for( int i = 0; i< projektils.size(); i++){
        Projektil* tmp = projektils.at(i);
        tmp->draw(deltaTimeInSeconds);
        // Wenn die maximale Distance erreichst ist Projektil löschen und Explision

        if(tmp->getDistance() >= tmp->getMaxDistance()){
             // Explosion hinzufügen
            Vector tmp2 = Vector(tmp->getPosition().X,tmp->getPosition().Y,tmp->getPosition().Z);
            this->explosions.push_back(new Explosion(tmp2));
            // Projektil löschen
            projektils.erase(projektils.begin());
        }
    }

    
}

void Vehicle::updateExplosions(float deltaTimeInSeconds){
    // Explosions darstellen
    /*for (list<Explosion*>::const_iterator it = explosions.begin(); it != explosions.end(); )
    {
        
        if (!(*it)->endExplosion)
        {
            (*it)->draw(deltaTimeInSeconds);
            ++it;
        }
        else
        {
            delete (*it);
            ++it;
            this->explosions.pop_front();
        }
    }*/
    for (int i = 0; i < explosions.size(); i++){
        Explosion* tmp = explosions.at(i);
        
        if(!(tmp->endExplosion)) {
            tmp->draw(deltaTimeInSeconds);
        }else {
            
            explosions.erase(explosions.begin());
            //delete(tmp);
        }
    }
}


Vector& Vehicle::getPosition(){
    return this->position;
}

void Vehicle::draw() {
    //BoundingBox lol = sceneObjChassisModel->getModel()->getBoundingBox();
    drawBB(newBB);
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

vector<Projektil*> Vehicle::getProjektils() {
    return projektils;
}

void Vehicle::spawnProjektil()
{
    
    // Startposition des Projektils, Position des Vehicles, Möglichkeit zur Änderung durch +1.0, etc... 
    Vector projektilPosition = *new Vector(this->position.X, this->position.Y, this->position.Z);
    
    // Richtung der Z-Achse
    Matrix direction = this->sceneObjCanonModel->getLocalTransform();
    Vector directionZ = direction.right();
    directionZ.normalize();
 
    // Projekttil Anzahl begrenzen wenn gewünscht
    //if(projektils.size() < 5) {
        projektils.push_back(new Projektil(projektilPosition, directionZ));
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