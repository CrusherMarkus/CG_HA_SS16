//
//  Camera.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <iostream>

#include "Vector.hpp"
#include "Matrix.hpp"

extern const unsigned int g_WindowWidth;
extern const unsigned int g_WindowHeight;

using namespace std;

class Camera
{
public:
    static Camera &getInstance() {
        static Camera instance;
        return instance;
    }
    
    Camera();
    Camera(Vector& Pos, Vector& Target, Vector& Up);
    
    Vector getPosition();
    Vector getTarget();
    Vector getUp();
    
    void setPosition( const Vector& Pos);
    void setTarget( const Vector& Target);
    void setUp( const Vector& Up);

    void mouseInput( int x, int y, int Button, int State);

    
    void apply();
    const Matrix& getViewMatrix() const;
    const Matrix& getProjectionMatrix() const;
    
    void update(float delta);
    void neuePos(int forwardbackward, int leftright);
    float forwardBackward;
    float leftRight;
protected:
    void pan( float dx, float dy);
    void zoom( float dz);
    void rotate( float x, float y );
    Vector getVSpherePos( float x, float y);
    Vector rotateAxisAngle( Vector v, Vector n, float a);
    
    Matrix m_ViewMatrix;
    Matrix m_ProjMatrix;
    Vector m_Position;
    Vector m_Target;
    Vector m_Up;
    Vector m_Panning;
    Vector m_Zoom;
    Vector m_Rotation;
    int m_LastMouseX;
    int m_LastMouseY;
};


#endif /* Camera_hpp */
