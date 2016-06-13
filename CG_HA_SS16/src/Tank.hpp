//
//  Tank.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include "Vector.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include <math.h>
#include "Camera.hpp"

extern const unsigned int g_WindowWidth;
extern const unsigned int g_WindowHeight;
extern Camera g_Camera;

class Tank
{
public:
    Tank(): chassisModel(), canonModel(), position(), speed(0), rotation(0) {}
    ~Tank();
    bool load(const char* ChassisModel, const char* CanonModel, const Vector& StartPos,
              const char* vertexShader, const char* fragmentShader);
    void steer(float ForwardBackward, float LeftRight);
    void aim(float MouseX, float MouseY);
    void update(float delta);
    void draw();
    
    float speed;
    float rotation;
protected:
    Model chassisModel;
    Model canonModel;
    
    Vector position;
};

#endif /* Tank_hpp */
