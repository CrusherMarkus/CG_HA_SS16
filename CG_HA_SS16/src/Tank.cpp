//
//  Tank.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Tank.hpp"

Tank::~Tank() {
}

bool Tank::load(const char* ChassisModel, const char* CanonModel, const Vector& StartPos,
                const char* vertexShader, const char* fragmentShader) {
    this->position = StartPos;
    
    if(!this->chassisModel.load(ChassisModel,  vertexShader, fragmentShader,false)
       || !this->canonModel.load(CanonModel, vertexShader, fragmentShader, false))
        return false;
    
    return true;
}

void Tank::steer(float ForwardBackward, float LeftRight) {
    this->speed = ForwardBackward;
    this->rotation = LeftRight;
}

void Tank::aim(float MouseX, float MouseY) {
    /* Dreisatzrechnung, rechne Mauskoordinaten von Fenstergröße in Werte von -1 bis 1
     
     Rechnen der Pixelkoordinaten des Mauszeigers in normalisierte
     Bildkoordinaten (x in[-1,1] und y in[-1,1]). Dies entspricht der inversen
     Viewport-Matrix. */
    float viewportX = (2.0f / g_WindowWidth) * (MouseX - (g_WindowWidth*0.5));
    float viewportY = (2.0f / g_WindowHeight) * (MouseY - (g_WindowHeight*0.5));
    
    
    /*	Richtungsvektor im Kameraraum bestimmen, indem die Projektionsmatrix  invers auf die neuen
     Mauszeigerkoordinaten angewendet wird. Die fehlende Z-Koordinate wird mit 0
     angenommmen. Das Ergebnis der Transformation ist ein Richtungsvektor im
     Kameraraum (View-Coordinates). */
    Matrix invertProjection = g_Camera.getProjectionMatrix();
    invertProjection.invert();
    Vector camDirection = invertProjection.transformVec4x4(Vector(viewportX, -viewportY, 0));
    
    
    /* Richtungsvektor in Welt-Koordinaten umrechnen.
     Nur Richtung des Vektors anpassen und nicht den Ursprung. */
    Matrix invertViewMatrix = g_Camera.getViewMatrix();
    invertViewMatrix.invert();
    Vector worldDirection = invertViewMatrix.transformVec3x3(camDirection);
    Vector rayOrigin = invertViewMatrix.translation(); //translation()=position der matrix
    
    
    /* Schnittpunkt mit y-Ebene berechnen
     Wähle 3 beliebige Punkte welche auf der y-Ebene liegen
     --> Algorithmus aus triangleIntersection */
    
    float s = 0.0;
    rayOrigin.triangleIntersection(worldDirection, Vector(1, 0, 0), Vector(0, 0, 0), Vector(0, 0, 1), s);
    
    this->position = rayOrigin + worldDirection * s;}

void Tank::update(float DeltaTime) {
    Matrix TM, RM, RTM, MH;
    static float distanceX = 0;
    static float distanceZ = 0;
    static float ang = 0;
    
    ang += this->rotation * 0.001 * DeltaTime;
    RM.rotationY(ang);
    
    distanceX += this->speed * RM.right().X * 0.001 * DeltaTime;
    distanceZ += this->speed * RM.right().Z * 0.001 * DeltaTime;
    
    TM.translation(distanceX, 0, distanceZ);
    
    RTM = TM * RM;
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(RTM);
    this->chassisModel.drawTriangles();
    glPopMatrix();
    
    /* TANK TOP CALC */
    
    MH.identity();
    
    Vector up(0, 1, 0);
    Vector forward = position - RTM.translation();
    forward.normalize();
    Vector right = up.cross(forward);
    
    MH.right(right);
    MH.up(up);
    MH.forward(forward);
    
    Matrix TMP;
    TMP.translation(RTM.translation());
    TMP.rotationY(-0.5*M_PI-ang);
    MH = RTM * (TMP*MH);
    
    glPushMatrix();
    glMultMatrixf(MH);
    this->canonModel.drawTriangles();
    glPopMatrix();

}

void Tank::draw() {
    float deltaTime;
    static int oldTimeSinceStart = 0;
    static int timeSinceStart;
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;
    
    this->update(deltaTime);
}
