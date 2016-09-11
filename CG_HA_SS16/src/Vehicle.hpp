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
#include "Model.hpp"
#include "Matrix.hpp"
#include "SceneObj.hpp"

using namespace std;

class Vehicle
{
public:
    Vehicle();
    ~Vehicle();
    bool load(const char* Model, const char* vertexShader, const char* fragmentShader);
    void steer(float ForwardBackward, float LeftRight);
    void update(float delta);
    void draw();
    
    Vector& getPosition();
    
    float getForwardBackward();
    float getLeftRight();
    
    Matrix m_MatrixVehicle;

protected:
    
    Model model;

    SceneObj sceneObj;
    
    Vector position;
    
    float forwardBackward;
    float leftRight;
    float angle;
    Vector p;
    
};


#endif /* Vehicle_hpp */
