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
    bb = enemy->getModel()->getBoundingBox();

    
    enemy->setScaling(Vector(0.5, 0.5, 0.5));

    this->maxHp = 100;
    this->hp = 100;
    this->alive = true;
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
        //cout << this->angleFacingMid << endl;
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
        
        newBB.setMax(bb.getMax()+this->position);
        newBB.setMin(bb.getMin()+this->position);
        //this->position = m_MatrixEnemy.translation();
        
        //cout << "position:" << this->position.X << "," << this->position.Y << "," << this->position.Z << endl;
        
    } else {
        
 
            updateProjektils(delta);
        if(this->projektils.size() < 1 ){
            spawnProjektil();
        }
        
        
    }
}


void Enemy::updateProjektils(float deltaTimeInSeconds){
    
    //cout << "updateProjektils" << endl;

    
    // Projektile
            for( int i = 0; i< projektils.size(); i++){
            Projektil* tmp = projektils.at(i);
            tmp->draw(deltaTimeInSeconds);
            
            if(tmp->getDistance() >= tmp->getMaxDistance()){
                  projektils.erase(projektils.begin());
            }
        }
    
        /*for (vector<Projektil*>::const_iterator it = (projektils).begin(); it != (projektils).end();)

        (**it).draw(deltaTimeInSeconds);
        
        if((**it).getPosition().length() >= (**it).getMaxDistance()) {
          
        }
        ++it;
    }*/
    
}
    
Vector& Enemy::getPosition(){
    return this->position;
}


bool Enemy::getIsHit(){
    return this->isHit;
}

void Enemy::draw() {
    drawBB(newBB);
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


void Enemy::spawnProjektil()
{
    //cout << "spawnProjektil" << endl;


    Vector projektilPosition = *new Vector(this->position.X, this->position.Y+1.1, this->position.Z+2.1);
    
    Matrix direction = this->enemy->getLocalTransform();
    Vector directionZ = direction.forward();
    //cout << "x: "<< directionZ.X << "y: " <<directionZ.Y<<"z: "<<directionZ.Z << endl;
    directionZ.normalize();

    
    projektils.push_back(new Projektil(this->position, directionZ));

}

void Enemy::setIsHit(bool isHit){
    this->isHit = isHit;
}
void Enemy::drawBB(BoundingBox &b){
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

short Enemy::getHp() const
{
    return this->hp;
}
void Enemy::setHp(short hp)
{
    this->hp = hp;
}
short Enemy::getMaxHp() const
{
    return this->maxHp;
}
void Enemy::setMaxHp(short maxHp)
{
    this->maxHp = maxHp;
}

bool Enemy::isAlive() const{
    return this->alive;
}
void Enemy::setAlive(bool alive){
    this->alive = alive;
}




