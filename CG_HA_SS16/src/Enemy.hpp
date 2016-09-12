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
#include "ModelBuilder.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include "SceneObj.hpp"
#include <list>
#include "Projektil.hpp"

using namespace std;

class Enemy{
    public:
        Enemy();
        ~Enemy();
        bool load(const char* Model, const Vector& v);
        void update(float delta);
        void draw();
        Vector& getPosition();
        void updateProjektils(float delta);
        bool getIsHit();
        float angleFacingMid;
        Matrix m_MatrixEnemy;
        SceneObj *enemy = new SceneObj();
        void setIsHit(bool);
        void drawBB(BoundingBox& b );
        void spawnProjektil();
        BoundingBox bb;
        BoundingBox newBB;
    
protected:
    vector<Projektil*> projektils;
    Vector position;
    
    Vector p;
    
    bool isHit;
};

#endif /* Enemy_hpp */
