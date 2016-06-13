//
//  VehicleCamera.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "VehicleCamera.hpp"

VehicleCamera::VehicleCamera() : m_Position(0.0f, 5.0f, -5.0f), m_Target(0.0f, 0.0f, 0.0f), m_Up(0.0f, 1.0f, 0.0f), m_Panning(0, 0, 0), m_Zoom(0, 0, 0), m_Rotation(0, 0, 0), m_Height(8.0f)
{
    m_ViewMatrix.identity();
    m_ProjMatrix.perspective(M_PI*65.0f / 180.0f, (double)g_WindowWidth / (double)g_WindowHeight, 0.045, 1000.0f);
}

VehicleCamera::VehicleCamera(Vector& Pos, Vector& Target, Vector& Up, float Height) : m_Panning(0, 0, 0), m_Zoom(0, 0, 0), m_Rotation(0, 0, 0), m_Height(Height)
{
    m_Up = Up;
    m_Position = Pos;
    m_Target = Target;
    m_ProjMatrix.perspective(M_PI*65.0f / 180.0f, (double)g_WindowWidth / (double)g_WindowHeight, 0.045, 1000.0f);
}

VehicleCamera::~VehicleCamera()
{
}

Vector VehicleCamera::getPosition()
{
    return m_Position + m_Panning + m_Zoom + m_Rotation;
}
Vector VehicleCamera::getTarget()
{
    return m_Target + m_Panning;
}
Vector VehicleCamera::getUp()
{
    return m_Up;
}
const Matrix& VehicleCamera::getViewMatrix() const {
    return m_ViewMatrix;
}
const Matrix& VehicleCamera::getProjectionMatrix() const {
    return m_ProjMatrix;
}
const float VehicleCamera::getHeight()
{
    return m_Height;
}
void VehicleCamera::setPosition(const Vector& Pos)
{
    m_Position = Pos;
    m_Panning = m_Rotation = m_Zoom = Vector(0, 0, 0);
}
void VehicleCamera::setTarget(const Vector& Target)
{
    m_Target = Target;
    m_Panning = Vector(0, 0, 0);
}
void VehicleCamera::setUp(const Vector& Up)
{
    m_Up = Up;
}
void VehicleCamera::setHeight(float height)
{
    m_Height = height;
}
void VehicleCamera::update(const Vector& Target, const Vector& forward, float distance,float height, float smooth,float deltaTime) {
    Vector wantedPos = Vector(0, 0, 0);
    Vector targetFixed = Target;
    
    Vector fwd = forward;
    wantedPos = Target - fwd.normalize() * distance;
    wantedPos.Y = height;
    Vector currentPos = getPosition();
    Vector diffVec = wantedPos - currentPos;
    Vector newCamPos = currentPos + diffVec * smooth * deltaTime; //Smooth value by Delta Time
    //newCamPos.Y = Math::lerp(currentPos.Y,height,smooth * deltaTime);
    
    setTarget(Target);
    setPosition(newCamPos);
    
    m_ViewMatrix.lookAt(getTarget(), m_Up, getPosition());
}
void VehicleCamera::apply()
{
    Vector Pos = getPosition();
    Vector Target = getTarget();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(m_ProjMatrix);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(m_ViewMatrix);
}
