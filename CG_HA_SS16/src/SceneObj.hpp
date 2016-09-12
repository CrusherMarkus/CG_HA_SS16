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
#include "Model.hpp"
#include "Matrix.hpp"
#include "Camera.hpp"

class SceneObj {
protected:
    std::string name;
    Model *model;
    
    Matrix localTransform;
    Vector translation;
    Vector translationTarget;
    Vector rotationAxis;
    float rotationAngle;
    float scalingTarget;
    Vector scaling;
    
public:
    SceneObj();
    SceneObj(const std::string& Name, const Vector& Translation, const Vector& RotationAxis, const float RotationAngle, const Vector& Scale, Model* pModel);
    ~SceneObj();
    
    bool operator==(const SceneObj &other);
    
    const std::string& getName() const;
    void setName(const std::string& Name);
    Model* getModel() const;
    void setModel(Model* pModel);
    
    Matrix getGlobalTransform() const;
    const Matrix &getLocalTransform() const;
    void setLocalTransform(const Vector& Translation, const Vector& RotationAxis, const float RotationAngle);
    void setLocalTransform(Matrix &transform);
    const Vector &getTranslation() const;
    const Vector &getRotationAxis() const;
    const float getRotationAngle() const;
    const Vector& getScaling() const;
    void setScaling(const Vector& Scaling);
    
    void computeBoundingBox();
    
    void scaleTo(float scaling);
    void translateTo(Vector &tranlation);
    bool needsTranslationUpdate();
    void rotateTo(float rotationAngle);
    void update(float delta);
};


#endif /* SceneObj_hpp */
