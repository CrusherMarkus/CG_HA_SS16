//
//  SceneObj.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 18.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef SceneObj_hpp
#define SceneObj_hpp

#include <stdio.h>
#include <iostream>
#include <set>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Model.hpp"
#include <math.h>

using namespace std;

class SceneObj {
public:
    SceneObj();
    SceneObj(string& Name, const Vector& Translation, const Vector& RotationAxis,
             const float RotationAngle, const Vector& Scale, Model model);
    ~SceneObj();
    
    const string& getName() const;
    const string& getModelName() const;
    const Matrix& getLocalTransform() const;
    const Vector& getScaling() const;
    const Vector& getRotationAxis() const;
    const Vector& getOrgTranslation() const;
    float getRotationAngle() const;

    Model& getModel();
    
    void setName(const string& Name);
    void setModelName(const string& Name);
    Model& loadModel(const char* Filename, bool FitSize, const char *vertexShader, const char *fragmentShader);

    void setLocalTransform(const Vector& Translation, const Vector& RotationAxis,
                           const float RotationAngle);
    void setLocalTransform(const Matrix& LocalTransform);
    void setScaling(const Vector& Scaling);
    void move(float x, float y, float z);
    void rotate(float angle, int axis);
    void update(float delta);
    
protected:
    string m_Name;
    string m_ModelName;
    Model m_Model;
    
    Matrix m_LocalTransform;
    Vector m_Scaling;
    Vector m_RotationAxis;
    Vector m_OrgTranslation;
    float m_RotationAngle;
    
};


#endif /* SceneObj_hpp */
