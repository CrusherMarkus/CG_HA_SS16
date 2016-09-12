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
    void draw();
    
    Vector& getPosition();
    float getForwardBackward();
    float getLeftRight();
    
    void spawnProjektil();
    
    list<Projektil*> getProjektils();
    BoundingBox bb;
    Matrix m_MatrixVehicle;
    Matrix m_MatrixCannon;
    SceneObj *sceneObjChassisModel = new SceneObj();
    void drawBB(BoundingBox& b );
    BoundingBox newBB;

protected:
    
        SceneObj *sceneObjCanonModel = new SceneObj();
    
    Vector position;
    
    float forwardBackward = 0.0;
    float leftRight = 0.0;
    Vector p;
    
    list<Projektil*> projektils;
    
};


#endif /* Vehicle_hpp */
