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

using namespace std;

class Vehicle
{
public:
    Vehicle();
    ~Vehicle();
    bool load(const char* Modelname);
    void steer(float ForwardBackward, float LeftRight);
    void update(float delta);
    void draw();
    
    Vector& getPosition();
    
    float getForwardBackward();
    float getLeftRight();
    
    Matrix m_MatrixVehicle;

protected:
    
    SceneObj *sceneObj = new SceneObj();
    
    Vector position;
    
    float forwardBackward;
    float leftRight;
    float angle;
    Vector p;
    
};


#endif /* Vehicle_hpp */
