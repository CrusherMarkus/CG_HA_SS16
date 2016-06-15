//
//  LightManager.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "LightManager.hpp"

LightManager::LightManager() {
    this->lightPosition = new Vector(0, 15, 0);
}
LightManager::~LightManager() {
    delete this->lightPosition;
}

LightManager& LightManager::getInstance()
{
    static LightManager instanz;
    return instanz;
}

const Vector *LightManager::getLightPosition() const {
    return this->lightPosition;
}

void LightManager::setLightPosition(const Vector &lightPosition) {
    *this->lightPosition = lightPosition;
}