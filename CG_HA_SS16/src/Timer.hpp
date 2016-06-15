//
//  Timer.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>

class Timer
{
public:
    Timer();
    ~Timer();
    
    unsigned int getLastFrameTime() const;
    unsigned int getDeltaTime() const;
    float getDeltaTimeInSeconds() const;
    const float getFPS();
    
    void calcTime();
private:
    unsigned int m_LastFrameTime=0;
    unsigned int m_DeltaTime=0;
    float m_DeltaTimeInSeconds = 0;
    unsigned int m_FrameCount = 0;
    float m_FPS = 0;
    unsigned int m_PreviousDeltaTime=0;
};

#endif /* Timer_hpp */
