//
//  main.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "Camera.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include "Tank.hpp"


const unsigned int g_WindowWidth=1024;
const unsigned int g_WindowHeight=768;
const Vector g_LightPos = Vector( 0,15,0);

int oldTimeSinceStart = 0;

Camera g_Camera;

Tank* g_Model = new Tank();

int g_MouseButton = 0;
int g_MouseState = 0;

void SetupDefaultGLSettings();
void DrawScene();
void MouseCallback(int Button, int State, int x, int y);
void MouseMoveCallback(int x, int y);
void KeyboardCallback( unsigned char key, int x, int y);
void MousePassiveMoveCallback( int x, int y);
void SpecialKeyboardCallback( int key, int x, int y);
void SpecialKeyboardUpCallback( int key, int x, int y);

int main(int argc, char * argv[])
{
    // initialize the glut system and create a window
    glutInitWindowSize(g_WindowWidth, g_WindowHeight);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("CG Praktikum");
    
    SetupDefaultGLSettings();
    
    glutDisplayFunc(DrawScene);
    glutMouseFunc(MouseCallback);
    glutKeyboardFunc(KeyboardCallback);
    glutMotionFunc(MouseMoveCallback);
    glutPassiveMotionFunc(MousePassiveMoveCallback);
    glutSpecialFunc(SpecialKeyboardCallback);
    glutSpecialUpFunc(SpecialKeyboardUpCallback);
    
    g_Model->load("objs/tank_bottom.obj", "objs/tank_top.obj", Vector(), "shader/vertex.glsl", "shader/fragment_toon.glsl");
    
    glutMainLoop();
    
}


void SetupDefaultGLSettings()
{
    glClearColor(0, 0, 0, 255);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (double)g_WindowWidth/(double)g_WindowHeight, 0.045f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Setup Light Color
    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 0.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    
    // Setup default material
    float diff[4] = {1,1,1,1};
    float amb[4]  = {0.2f,0.2f,0.2f,1};
    float spec[4] = {0.5f,0.5f,0.5f,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMateriali(GL_FRONT, GL_SHININESS, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    
}

void DrawGroundGrid()
{
    const float GridSize=10.0f;
    const unsigned int GridSegments=20;
    const float GridStep=GridSize/(float)GridSegments;
    const float GridOrigin=-GridSize*0.5f;
    
    glDisable( GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    for( unsigned int i=0; i<GridSegments+1; i++)
    {
        float itpos=GridOrigin + GridStep*(float)i;
        glVertex3f(itpos, 0, GridOrigin);
        glVertex3f(itpos, 0, GridOrigin+GridSize);
        
        glVertex3f(GridOrigin, 0, itpos);
        glVertex3f(GridOrigin+GridSize, 0, itpos);
        
    }
    glEnd();
    glEnable( GL_LIGHTING);
    
}

void MouseCallback(int Button, int State, int x, int y)
{
    g_MouseButton = Button;
    g_MouseState = State;
    g_Camera.mouseInput(x,y,Button,State);
    
}

void MouseMoveCallback( int x, int y)
{
    g_Camera.mouseInput(x,y,g_MouseButton,g_MouseState);
}

void MousePassiveMoveCallback( int x, int y)
{
	g_Model->aim(x, y);
}

void KeyboardCallback( unsigned char key, int x, int y)
{
    // function is called if a regular keyboard button is pressed
}

void SpecialKeyboardCallback( int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            g_Model->steer(1.f, 0);
            break;
        case GLUT_KEY_DOWN:
            g_Model->steer(-1.f, 0);
            break;
        case GLUT_KEY_LEFT:
            g_Model->steer(0, 1.f);
            break;
        case GLUT_KEY_RIGHT:
            g_Model->steer(0, -1.f);
            break;
        default:
            break;
    }
}

void SpecialKeyboardUpCallback( int key, int x, int y)
{
    g_Model->steer(0, 0);
}

void DrawScene()
{
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat lpos[4];
    lpos[0]=g_LightPos.X; lpos[1]=g_LightPos.Y; lpos[2]=g_LightPos.Z; lpos[3]=1;
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    
    g_Camera.apply();
	g_Model->draw();

    DrawGroundGrid();
    
    
    // call your tank & Scene class-members here
    
    glutSwapBuffers();
    glutPostRedisplay();
    
}
