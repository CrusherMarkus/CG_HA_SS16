//
//  SceneObj.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 18.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "SceneObj.hpp"

#ifndef DEG2RAD
#define DEG2RAD(x) ((x)/180.0*M_PI)
#define RAD2DEG(x) ((x)/M_PI*180.0)
#endif

SceneObj::SceneObj() {
    this->m_Scaling = Vector();
    this->m_LocalTransform = Matrix();
}

SceneObj::SceneObj(string& Name, const Vector& Translation, const Vector& RotationAxis,
                   const float RotationAngle, const Vector& Scale, Model model) {
    SceneObj();
    
    this->m_Name = Name;
    this->m_LocalTransform.translation(Translation);
    this->m_LocalTransform.rotationAxis(RotationAxis, RotationAngle);
    this->m_Scaling = Scale;
    this->m_Model = model;
}

SceneObj::~SceneObj() {
}

const string& SceneObj::getName() const {
    return this->m_Name;
}

const string& SceneObj::getModelName() const {
    return this->m_ModelName;
}

const Matrix& SceneObj::getLocalTransform() const {
    return this->m_LocalTransform;
}

const Vector& SceneObj::getScaling() const {
    return this->m_Scaling;
}

const Vector& SceneObj::getRotationAxis() const {
    return this->m_RotationAxis;
}

float SceneObj::getRotationAngle() const {
    return this->m_RotationAngle;
}

const Vector& SceneObj::getOrgTranslation() const {
    return this->m_OrgTranslation;
}


Model& SceneObj::getModel() {
    return this->m_Model;
}

void SceneObj::setName(const string& Name) {
    this->m_Name = Name;
}

void SceneObj::setModelName(const string& Name) {
    this->m_ModelName = Name;
}

Model& SceneObj::loadModel(const char* Filename, bool FitSize, const char *vertexShader, const char *fragmentShader) {
    // set 'fitSize' to false since scaling is handled via matrix transform
    // otherwise the bounding box would not fit any more.
    if(!m_Model.load(Filename, false, vertexShader, fragmentShader)) {
        cerr << "Could not load model bottom (" << Filename << ")" << endl;

    }
    
    return m_Model;
}

void SceneObj::setLocalTransform(const Vector& Translation, const Vector& RotationAxis,
                                 const float RotationAngle) {
    Matrix trans, rot;
    
    m_RotationAxis = RotationAxis;
    m_RotationAngle = RotationAngle;
    m_OrgTranslation = Translation;
    
    trans.translation(Translation);
    rot.rotationAxis(RotationAxis, DEG2RAD(RotationAngle));
    
    this->m_LocalTransform = trans * rot;
}

void SceneObj::setLocalTransform(const Matrix& LocalTransform) {
    this->m_LocalTransform = LocalTransform;
}

void SceneObj::setScaling(const Vector& Scaling) {
    this->m_Scaling = Scaling;
}

void SceneObj::move(float x, float y, float z) {
    // set scaling of movement here, since the GLUI function does not work
    float scale = .01f;
    
    m_OrgTranslation.X += x * scale;
    m_OrgTranslation.Y += y * scale;
    m_OrgTranslation.Z += z * scale;
}

/*
 axis: 0 = x; 1 = y; 2 = z
 */
void SceneObj::rotate(float angle, int axis) {
    m_RotationAngle = angle;
    
    m_RotationAxis = Vector();
    
    if(axis == 0)
        m_RotationAxis.X = 1;
    if(axis == 1)
        m_RotationAxis.Y = 1;
    if(axis == 2)
        m_RotationAxis.Z = 1;
}

void SceneObj::update(float delta) {
    Matrix TM, RM;
    
    RM.rotationAxis(m_RotationAxis, DEG2RAD(m_RotationAngle));
    TM.translation(m_OrgTranslation.X, m_OrgTranslation.Y, m_OrgTranslation.Z);
    
    m_LocalTransform = TM * RM;
}
