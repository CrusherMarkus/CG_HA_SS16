//
//  LightManager.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef LightManager_hpp
#define LightManager_hpp

#include <stdio.h>
#include "Vector.hpp"

class LightManager {
    private:
        LightManager();
        ~LightManager();
        Vector *lightPosition;
    
    public:
        const Vector *getLightPosition() const;
        void setLightPosition(const Vector &lightPosition);
        static LightManager& getInstance();


};

#endif /* LightManager_hpp */
