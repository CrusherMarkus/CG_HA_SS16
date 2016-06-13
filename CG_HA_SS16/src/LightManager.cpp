//
//  LightManager.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "LightManager.hpp"

#include <sstream>
#include <string>


LightManager::LightManager()
{
}


LightManager& LightManager::instance()
{
    static LightManager instanz;
    return instanz;
}

LightManager::~LightManager()
{
    
}

void LightManager::setCamera(VehicleCamera * camera)
{
    m_Camera = camera;
}

