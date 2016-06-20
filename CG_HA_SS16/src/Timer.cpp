//
//  Timer.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Timer.hpp"
#include <GLUT/GLUT.h>

Timer::Timer()
{
}

Timer::~Timer()
{
}

unsigned int Timer::getLastFrameTime() const
{
    return m_LastFrameTime;
}

unsigned int Timer::getDeltaTime() const
{
    return m_DeltaTime;
}

float Timer::getDeltaTimeInSeconds() const
{
    return m_DeltaTimeInSeconds;
}

void Timer::calcTime()
{
    m_PreviousDeltaTime = m_DeltaTime;
    cout << "m_PreviousDeltaTime" << m_PreviousDeltaTime << endl;
    m_DeltaTime = glutGet(GLUT_ELAPSED_TIME) - m_LastFrameTime;
    cout << "m_DeltaTime" << m_DeltaTime << endl;
    m_LastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    cout << "m_LastFrameTime" << m_LastFrameTime << endl;
    m_DeltaTimeInSeconds = m_DeltaTime / 1000.0f;
    cout << "m_DeltaTimeInSeconds" << m_DeltaTimeInSeconds << endl;
    m_FrameCount++;
    
    if (m_DeltaTime > 1000) {
        m_FPS = (m_FrameCount / m_DeltaTimeInSeconds)*1000;
        m_FrameCount = 0;
    }
}

const float Timer::getFPS() {
    return m_FPS;
}