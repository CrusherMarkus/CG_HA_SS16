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
#include "Game.hpp"
#include <GLUI/GLUI.h>
#include <iomanip>


//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
const unsigned int g_WindowWidth=1024;
const unsigned int g_WindowHeight=768;

const Vector g_LightPos = Vector( 0,100,10);

Game g_Game;
Timer g_Timer;
Camera g_Camera;
GLUI g_Glui;

int g_MouseButton = 0;
int g_MouseState = 0;

int forwardbackward =0;
int leftright =0;

//  The id of the main window
GLuint g_MainWindow;

GLUI_StaticText* gluiStaticText_Time;
GLUI_StaticText* gluiStaticText_VehiclePositionX;
GLUI_StaticText* gluiStaticText_VehiclePositionY;
GLUI_StaticText* gluiStaticText_VehiclePositionZ;
GLUI_StaticText* gluiStaticText_VehicleForwardBackward;
GLUI_StaticText* gluiStaticText_VehicleLeftRight;
GLUI_StaticText* gluiStaticText_ProjectilesSize;
GLUI_StaticText* gluiStaticText_CameraPositionX;
GLUI_StaticText* gluiStaticText_CameraPositionY;
GLUI_StaticText* gluiStaticText_CameraPositionZ;
GLUI_StaticText* gluiStaticText_FPS;
GLUI_StaticText* gluiStaticText_EnemySize;
GLUI_StaticText* gluiStaticText_DefenceHp;


void SetupGLUI();
void drawAxes(GLdouble length);
void centerOnScreen();
void idle();
void SetupDefaultGLSettings();
void display();
void MouseCallback(int Button, int State, int x, int y);
void MouseMoveCallback(int x, int y);
void KeyboardCallback( unsigned char key, int x, int y);
void MousePassiveMoveCallback( int x, int y);
void SpecialKeyboardCallback( int key, int x, int y);
void SpecialKeyboardUpCallback( int key, int x, int y);



int main(int argc, char * argv[])
{
    
    //  Set the window x and y coordinates such that the
    //  window becomes centered
    centerOnScreen ();
    
    //  Connect to the windowing system + create a window
    //  with the specified dimensions and position
    //  + set the display mode + specify the window title.
    glutInit(&argc, argv);
    glutInitWindowSize(g_WindowWidth, g_WindowHeight);
    glutInitWindowPosition (window_x, window_y);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    g_MainWindow = glutCreateWindow("CG Hausarbeit");
    
    SetupDefaultGLSettings();
    
    glutDisplayFunc(display);
    glutMouseFunc(MouseCallback);
    glutKeyboardFunc(KeyboardCallback);
    glutMotionFunc(MouseMoveCallback);
    glutPassiveMotionFunc(MousePassiveMoveCallback);
    glutSpecialFunc(SpecialKeyboardCallback);
    glutSpecialUpFunc(SpecialKeyboardUpCallback);
    
    
    g_Game.initialize();
    
    //  Setup all GLUI stuff
    SetupGLUI();
    
    //  Start GLUT event processing loop
    glutMainLoop();
    
}

void SetupGLUI() {
    GLUI *glui = GLUI_Master.create_glui_subwindow(g_MainWindow, GLUI_SUBWINDOW_RIGHT);
    GLUI_Panel* gameinfo_panel = glui->add_panel("Spielinformationen");
    
    glui->add_statictext_to_panel(gameinfo_panel, "Zeit");
    gluiStaticText_Time = glui->add_statictext_to_panel(gameinfo_panel, "- Sekunden");
    /*glui->add_statictext_to_panel(gameinfo_panel, "FPS");
    gluiStaticText_FPS = glui->add_statictext_to_panel(gameinfo_panel, "-");*/

    
    GLUI_Panel* vehicle_panel = glui->add_panel("Vehicle");
    glui->add_statictext_to_panel(vehicle_panel, "Position");
    
    gluiStaticText_VehicleForwardBackward = glui->add_statictext_to_panel(vehicle_panel, "-");
    gluiStaticText_VehicleLeftRight = glui->add_statictext_to_panel(vehicle_panel, "-");

    gluiStaticText_VehiclePositionX = glui->add_statictext_to_panel(vehicle_panel, "-");
    gluiStaticText_VehiclePositionY = glui->add_statictext_to_panel(vehicle_panel, "-");
    gluiStaticText_VehiclePositionZ = glui->add_statictext_to_panel(vehicle_panel, "-");
    
    gluiStaticText_ProjectilesSize = glui->add_statictext_to_panel(vehicle_panel, "-");
    
    GLUI_Panel* camera_panel = glui->add_panel("Camera");
    glui->add_statictext_to_panel(camera_panel, "Position");
    
    gluiStaticText_CameraPositionX = glui->add_statictext_to_panel(camera_panel, "-");
    gluiStaticText_CameraPositionY = glui->add_statictext_to_panel(camera_panel, "-");
    gluiStaticText_CameraPositionZ = glui->add_statictext_to_panel(camera_panel, "-");
    
    
    GLUI_Panel* enemy_panel = glui->add_panel("Gegner");
    gluiStaticText_EnemySize = glui->add_statictext_to_panel(enemy_panel, "-");
    
    GLUI_Panel* defence_panel = glui->add_panel("Verteidigung");
    gluiStaticText_DefenceHp = glui->add_statictext_to_panel(defence_panel, "-");
    

    
    //  Let the GLUI window know where its main graphics window is
    glui->set_main_gfx_window(g_MainWindow);
    
    //  Set idle function
    GLUI_Master.set_glutIdleFunc(idle);
    
    GLUI_Master.sync_live_all();
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen ()
{
    window_x = (glutGet (GLUT_SCREEN_WIDTH) - g_WindowWidth)/2;
    window_y = (glutGet (GLUT_SCREEN_HEIGHT) - g_WindowHeight)/2;
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
    
    
    // x-axis
    glColor3f(0.5f, 0, 0);
    glVertex3f(-10, 0, 0);
    glVertex3f( 10, 0, 0);
    
    // z-axis
    glColor3f(0,0,0.5f);
    glVertex3f(0, 0, -10);
    glVertex3f(0, 0,  10);
    
    
    glEnd();
    glEnable( GL_LIGHTING);
    
}

void MouseCallback(int Button, int State, int x, int y)
{
    g_MouseButton = Button;
    g_MouseState = State;
    g_Camera.mouseInput(x,y,Button,State);
    
    
    switch (Button)
    {
        case  GLUT_LEFT_BUTTON:
            if(State != 0)
            {
                g_Game.m_Vehicle.spawnProjektil();
            }
            break;
    }
}



void MouseMoveCallback( int x, int y)
{
    g_Camera.mouseInput(x,y,g_MouseButton,g_MouseState);
}

void MousePassiveMoveCallback( int x, int y)
{
    // function is called if the mouse moves without pressing any button.
}

void KeyboardCallback( unsigned char key, int x, int y)
{
    // function is called if a regular keyboard button is pressed
}

void SpecialKeyboardCallback( int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            forwardbackward = 1;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        case GLUT_KEY_DOWN:
            forwardbackward = -1;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        case GLUT_KEY_LEFT:
            leftright = 1;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        case GLUT_KEY_RIGHT:
            leftright = -1;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        default:
            break;
    }
}

void SpecialKeyboardUpCallback( int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            forwardbackward = 0;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        case GLUT_KEY_DOWN:
            forwardbackward = 0;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        case GLUT_KEY_LEFT:
            leftright = 0;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        case GLUT_KEY_RIGHT:
            leftright = 0;
            g_Game.m_Vehicle.steer(forwardbackward, leftright);
            //g_Camera.neuePos(forwardbackward,leftright);
            break;
        default:
            break;
    }

}

void updateGlui() {
    float gameTime = (float)g_Timer.getLastFrameTime()/1000;
    string s = to_string(gameTime);
    s.append(" Sekunden");
    gluiStaticText_Time->set_text(s.c_str());
    
    
    /*float fps = (float) g_Timer.getFPS();
    s = to_string(fps);
    gluiStaticText_FPS->set_text(s.c_str());*/
    
    
    Vector vehiclePosition = g_Game.m_Vehicle.getPosition();
    gluiStaticText_VehiclePositionX->set_text((to_string(vehiclePosition.X).insert(0, "X:")).c_str());
    gluiStaticText_VehiclePositionY->set_text((to_string(vehiclePosition.Y).insert(0, "Y:")).c_str());
    gluiStaticText_VehiclePositionZ->set_text((to_string(vehiclePosition.Z).insert(0, "Z:")).c_str());
    
    float forwardBackward = g_Game.m_Vehicle.getForwardBackward();
    float leftRight = g_Game.m_Vehicle.getLeftRight();
    gluiStaticText_VehicleForwardBackward->set_text((to_string(forwardBackward).insert(0, "forwardBackward:")).c_str());
    gluiStaticText_VehicleLeftRight->set_text((to_string(leftRight).insert(0, "leftRight:")).c_str());

    
    int projectileSize = g_Game.m_Vehicle.getProjektils().size();
    gluiStaticText_ProjectilesSize->set_text((to_string(projectileSize).insert(0, "Anzahl Projektile:")).c_str());
    
    Vector cameraPosition = g_Camera.getPosition();
    gluiStaticText_CameraPositionX->set_text((to_string(cameraPosition.X).insert(0, "X:")).c_str());
    gluiStaticText_CameraPositionY->set_text((to_string(cameraPosition.Y).insert(0, "Y:")).c_str());
    gluiStaticText_CameraPositionZ->set_text((to_string(cameraPosition.Z).insert(0, "Z:")).c_str());
    
    int enemySize = g_Game.getEnemySize();
    gluiStaticText_EnemySize->set_text((to_string(enemySize).insert(0, "Anzahl Gegner:")).c_str());
    
    int defenceHp = g_Game.m_DefenseObject.getHp();
    cout << "defenceHp:" << defenceHp << endl;
    gluiStaticText_DefenceHp->set_text((to_string(defenceHp).insert(0, "Lebenpunkte:")).c_str());

}

//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display
//	OpenGL contents on the window.
//-------------------------------------------------------------------------
void display()
{
    //  Clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    
    g_Game.gameLoop();
    g_Camera.update(g_Timer.getDeltaTime());
    
    updateGlui();
        
    DrawGroundGrid();
    
    //  Swap contents of backward and forward frame buffers
    glutSwapBuffers();
}

//-------------------------------------------------------------------------
//  Idle Callback function.
//
//  Set the main_window as the current window to avoid sending the
//  redisplay to the GLUI window rather than the GLUT window.
//  Call the Sleep function to stop the GLUI program from causing
//  starvation.
//-------------------------------------------------------------------------
void idle ()
{
    glutSetWindow (g_MainWindow);
    glutPostRedisplay ();
}
