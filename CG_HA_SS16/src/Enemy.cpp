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
    if(x.X >= 0.0){
        angleFacingMid = acos(x.dot(*new Vector(0.0,0.0,1.0)));
        angleFacingMid = angleFacingMid*(180/M_PI);
        angleFacingMid = angleFacingMid +180;
        angleFacingMid = angleFacingMid/(180/M_PI);
    }
    else {
        angleFacingMid = acos(x.dot(*new Vector(0.0,0.0,-1.0)));
        
    }
    
    cout << angleFacingMid << endl;
    enemy->setScaling(Vector(1.0,1.0,1.0));
    enemy->setLocalTransform(v, Vector(0.0,1.0,0.0), angleFacingMid);

    Model *newModel = modelBuilder.buildModel(modelname);
    enemy->setModel(newModel);
    enemy->computeBoundingBox();

    this->position = v;
    return true;

}



void Enemy::update(float delta){
    if (isHit) {
        return;
    }
    if (this->position.length() > 5){
        Vector direction(-this->position.X/100,0,-this->position.Z/100);
        this->m_MatrixEnemy = enemy->getLocalTransform();
        this->position += direction;
        Matrix tm;
        //tm.translation(this->position);
        Matrix rm;
        cout << this->angleFacingMid << endl;
        rm = rm.rotationY(angleFacingMid);
        //m_MatrixEnemy.rotationY(this->angleFacingMid);
        Vector moveVec = m_MatrixEnemy.forward();
        
        //cout << "position:" << moveVec.X << "," << moveVec.Y << "," << moveVec.Z << endl;
        
        //Vector translationV = m_MatrixEnemy.translation();
        //Vector newTrans = translationV+direction;
        //m_MatrixEnemy.translation(newTrans);
        
        //m.translation(this->position.X*0.9,0,this->position.Z*0.9);
        tm.translation(this->position);
        
        m_MatrixEnemy.rotationY(angleFacingMid);
        tm *= m_MatrixEnemy;
        //m_MatrixEnemy *= tm;
        // m_MatrixEnemy *= rm;
        enemy->setLocalTransform(tm);
        enemy->computeBoundingBox();
        //this->position = m_MatrixEnemy.translation();
        
        //cout << "position:" << this->position.X << "," << this->position.Y << "," << this->position.Z << endl;
    }
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
    //glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(enemy->getGlobalTransform() * m.scale(enemy->getScaling()));
    enemy->getModel()->draw();
    glPopMatrix();
    
}



void Enemy::setIsHit(bool isHit){
    this->isHit = isHit;
}




