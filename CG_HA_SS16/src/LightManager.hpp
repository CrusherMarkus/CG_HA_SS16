//
//  LightManager.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef LightManager_hpp
#define LightManager_hpp

#include <stdio.h>

#include <vector>
#include "VehicleCamera.hpp"

/*Singleton für alle Lichter des Spiels da jeder Shader alle Lichter benutzt
 *Übergibt alle Lichter an den shader welcher bei apply übergeben wird
 */


class LightManager
{
public:
    static LightManager& instance();
    ~LightManager();
    
    void setCamera(VehicleCamera *camera);
    
private:
    LightManager();
    LightManager(const LightManager&);
    LightManager & operator=(const LightManager&);
    
    VehicleCamera* m_Camera;

};

#endif /* LightManager_hpp */
