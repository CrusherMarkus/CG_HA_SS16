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
#include "DisplayText.hpp"
#include "ModelBuilder.hpp"

using namespace std;

class Vehicle
{
public:
    Vehicle();
    ~Vehicle();
    bool load(const char* Model, const Vector& StartPos,
              const char* vertexShader, const char* fragmentShader);
    void steer(float ForwardBackward, float LeftRight);

    void update(float delta);
    void draw();
    
    Matrix m_MatrixVehicle;
    float forwardBackward;
    Vector& getPosition();

protected:
    
    Model *model;
    
    Matrix cannonmatrix;
    Vector position;
    double velocity;
    float leftRight;
    float drehung;
    Vector p;
    
    DisplayText* displayText;
};


#endif /* Vehicle_hpp */
