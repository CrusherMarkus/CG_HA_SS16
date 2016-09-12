//
//  DefenseObject.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef DefenseObject_hpp
#define DefenseObject_hpp

#include <stdio.h>
#include "ModelBuilder.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include "SceneObj.hpp"

class DefenseObject
{
public:
    DefenseObject();
    ~DefenseObject();
    bool load(const char* DefenseModel, const Vector& StartPos);

    void update(float delta);

    void draw();
    
    Vector& getPosition();
    
    Matrix m_MatrixDefenseObject;

    short getHp() const;
    void setHp(short hp);
    
protected:
    
    short hp;
    
    SceneObj *defenseObject = new SceneObj();
    Vector position;
    Vector p;

};

#endif /* DefenseObject_hpp */
