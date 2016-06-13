//
//  VehicleCamera.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef VehicleCamera_hpp
#define VehicleCamera_hpp

#include <stdio.h>

#include "Vector.hpp"
#include "Matrix.hpp"
#include <math.h>
#include <GLUT/GLUT.h>

extern const unsigned int g_WindowWidth;
extern const unsigned int g_WindowHeight;

class VehicleCamera
{
public:
    VehicleCamera();
    ~VehicleCamera();
    VehicleCamera(Vector& Pos, Vector& Target, Vector& Up, float Height=10.0f);
    
    Vector getPosition();
    Vector getTarget();
    Vector getUp();
    
    void setPosition(const Vector& Pos);
    void setTarget(const Vector& Target);
    void setUp(const Vector& Up);
    void setHeight(float height);
    
    const Matrix& getViewMatrix() const;
    const Matrix& getProjectionMatrix() const;
    const float getHeight();
    
    void apply();
    void update(const Vector& Target, const Vector& forward, float distance,float height, float smooth,float deltaTime);
protected:
    
    Matrix m_ViewMatrix;
    Matrix m_ProjMatrix;
    Vector m_Position;
    Vector m_Target;
    Vector m_Up;
    Vector m_Panning;
    Vector m_Zoom;
    Vector m_Rotation;
    float m_Height;
};

#endif /* VehicleCamera_hpp */
