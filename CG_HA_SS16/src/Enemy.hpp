//
//  Enemy.hpp
//  CG_HA_SS16
//
//  Created by Albert Hildenberg on 10/09/16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "Model.hpp"
#include "Matrix.hpp"
#include "SceneObj.hpp"

using namespace std;

class Enemy{
    public:
        Enemy();
        ~Enemy();
        bool load(const char* Model, const char* vertexShader, const char* fragmentShader, const Vector& v);
        void update(float delta);
        void draw();
        Vector& getPosition();
        bool getIsHit();
        float angleFacingMid;
        Matrix m_MatrixEnemy;
    
protected:
    
    Model model;
    
    SceneObj sceneObj;
    
    Vector position;
    
    Vector p;
    
    bool isHit;
};

#endif /* Enemy_hpp */
