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

class Vehicle
{
public:
    Vehicle(): model(), position(), speed(0), rotation(0) {}
    ~Vehicle();
    bool load(const char* Model, const Vector& StartPos,
              const char* vertexShader, const char* fragmentShader);
    void steer(float ForwardBackward, float LeftRight);

    void update(float delta);
    void draw();
    
    const Matrix& getModelViewMatrix() const;
    
    void setPosition(const Vector& position);
    const Vector& getPosition() const;
protected:
    Model model;
    
    float speed;
    float rotation;

	Vector position;
    float left;
    float right;
    float steerAngle;
    float heading;
    
    Matrix m_VehicleMatrix;
};


#endif /* Vehicle_hpp */
