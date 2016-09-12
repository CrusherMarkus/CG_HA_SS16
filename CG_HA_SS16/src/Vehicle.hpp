//
//  Vehicle.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include "ModelBuilder.hpp"
#include "Matrix.hpp"
#include "SceneObj.hpp"
#include "Model.hpp"
#include <list>
#include "Projektil.hpp"
#include "Explosion.hpp"

extern Camera g_Camera;
extern const unsigned int g_WindowWidth;
extern const unsigned int g_WindowHeight;

using namespace std;

class Vehicle
{
public:
    Vehicle();
    ~Vehicle();
    bool load(const char* ChassisModel, const char* CanonModel, const Vector& StartPos);
    void steer(float ForwardBackward, float LeftRight);
    void update(float delta);
    void updateProjektils(float delta);
    void updateExplosions(float delta);
    void draw();
    
    Vector& getPosition();
    float getForwardBackward();
    float getLeftRight();
    
    const Matrix& getModelViewMatrix() const;

    
    void spawnProjektil();
    
    list<Projektil*> getProjektils();
    
    Matrix m_MatrixVehicle;
    Matrix m_MatrixCannon;
    void drawBB(BoundingBox& b );
    
    SceneObj *sceneObjCanonModel = new SceneObj();
    SceneObj *sceneObjChassisModel = new SceneObj();
    SceneObj *sceneObjmodel = new SceneObj();
    
protected:
    


    Vector position;
    
    float forwardBackward = 0.0;
    float leftRight = 0.0;
    Vector p;
    
    list<Projektil*> projektils;
    list<Explosion*> explosions;
    
};


#endif /* Vehicle_hpp */
