//
//  Enemy.cpp
//  CG_HA_SS16
//
//  Created by Albert Hildenberg on 10/09/16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Enemy.hpp"


Enemy::Enemy() {
}

Enemy::~Enemy() {
    
}

bool Enemy::load(const char* modelname, const Vector& v) {
    
    ModelBuilder modelBuilder;
    
    Vector x = v;
    x= x.normalize();
    
    this->angleFacingMid = acos(x.dot(*new Vector(0.0,0.0,1.0)));
    //angleFacingMid = angleFacingMid*(180/M_PI);
    if(x.X >= 0.0){
        angleFacingMid = acos(x.dot(*new Vector(0.0,0.0,1.0)));
        //angleFacingMid = angleFacingMid*(180/M_PI);
        //angleFacingMid = angleFacingMid -180;
    }
    else {
        angleFacingMid = acos(x.dot(*new Vector(0.0,0.0,-1.0)));
        //angleFacingMid = angleFacingMid*(180/M_PI);
  
    }

    cout << angleFacingMid << endl;
    //sceneObj->setScaling(Vector(1.0,1.0,1.0));
    //sceneObj->setLocalTransform(v, Vector(0.0,1.0,0.0), angleFacingMid);
    Model *newModel = modelBuilder.buildModel(modelname);
    
    sceneObj->setModel(newModel);
    
    sceneObj->setLocalTransform(Vector(), Vector(1, 0, 0), 0);
    sceneObj->setScaling(Vector(1, 1, 1));

    sceneObj->computeBoundingBox();

    return true;
}



void Enemy::update(float delta){
    if (isHit) {
        return;
    }
    if (this->position.length() > 5){
        Vector direction(-this->position.X/100,0,-this->position.Z/100);
        this->m_MatrixEnemy = sceneObj->getLocalTransform();
        this->position += direction;
        Matrix tm;
        //tm.translation(-this->position);
        Matrix rm;
        rm = rm.rotationY(angleFacingMid);
        //m_MatrixEnemy.rotationY(this->angleFacingMid);
        Vector moveVec = m_MatrixEnemy.forward();
        
        //cout << "position:" << moveVec.X << "," << moveVec.Y << "," << moveVec.Z << endl;
        
        //Vector translationV = m_MatrixEnemy.translation();
        //Vector newTrans = translationV+direction;
        //m_MatrixEnemy.translation(newTrans);
        
        //m.translation(this->position.X*0.9,0,this->position.Z*0.9);
        tm.translation(this->position);
        m_MatrixEnemy = rm*tm;
        
        sceneObj->setLocalTransform(m_MatrixEnemy);
        //this->position = m_MatrixEnemy.translation();
        
         //cout << "position:" << this->position.X << "," << this->position.Y << "," << this->position.Z << endl;
    }
    /*
    m_MatrixEnemy = sceneObj.getLocalTransform();
    
    Matrix rm;
    Matrix m;
    
    
    Begrenzung links/rechts
     if((m_MatrixVehicle.translation().X > 4 && leftRight == 1) || (m_MatrixVehicle.translation().X < -4 && leftRight == -1)){
     cout << "X-Grenze erreicht!" << endl;
     } else {
     
    m.translation(1*3*delta, 0, 0);
    m_MatrixEnemy *= m;
    m.translation(0, 0, 1*3*delta);
    m_MatrixEnemy *= m;
    /*
     this->angle += this->leftRight *delta/ 1000;
     
     if(this->angle >= M_PI * 2 || this->angle <= -M_PI * 2){
     this->angle = 0;
     }
     
     
    //m_MatrixVehicle = m*rm;
    
    //cout << "angle:"<<this->angle << endl;
    
    
    sceneObj.setLocalTransform(m_MatrixEnemy);*/

}
Vector& Enemy::getPosition(){
    return this->position;
}


bool Enemy::getIsHit(){
    return this->isHit;
}

void Enemy::draw() {
    
    Matrix m;
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1.0f,0,0);
    glVertex3f(p.X, p.Y, p.Z);
    glEnd();
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(sceneObj->getGlobalTransform() * m.scale(sceneObj->getScaling()));
    sceneObj->getModel()->draw();
    glPopMatrix();
    
}



