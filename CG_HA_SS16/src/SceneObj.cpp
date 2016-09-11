//
//  SceneObj.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 18.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "SceneObj.hpp"

SceneObj::SceneObj() {
    this->model = NULL;
}

SceneObj::SceneObj(const std::string &name, const Vector &translation, const Vector &rotationAxis, const float rotationAngle, const Vector &scale, Model *model) {
    this->name = name;
    this->scaling = scale;
    this->model = model;
    
    this->setLocalTransform(translation, rotationAxis, rotationAngle);
}

SceneObj::~SceneObj() {
    delete this->model;
}

bool SceneObj::operator==(const SceneObj &other) {
    return this->getName() == other.getName();
}

const std::string& SceneObj::getName() const {
    return this->name;
}

void SceneObj::setName(const std::string& Name) {
    this->name = Name;
}

Model *SceneObj::getModel() const {
    return this->model;
}

void SceneObj::setModel(Model* pModel) {
    this->model = pModel;
}


Matrix SceneObj::getGlobalTransform() const {
    return this->localTransform;
}

const Matrix &SceneObj::getLocalTransform() const {
    return this->localTransform;
}

void SceneObj::setLocalTransform(const Vector &translation, const Vector &rotationAxis, const float rotationAngle) {
    this->translation = translation;
    this->rotationAxis = rotationAxis;
    this->rotationAngle = rotationAngle;
    
    Matrix translationMatrix;
    Matrix rotationMatrix;
    
    translationMatrix.translation(translation);
    rotationMatrix.rotationAxis(rotationAxis, rotationAngle);
    
    this->localTransform = translationMatrix * rotationMatrix;
}

void SceneObj::setLocalTransform(Matrix &transform) {
    this->localTransform = transform;
}

const Vector &SceneObj::getTranslation() const {
    return this->translation;
}

const Vector &SceneObj::getRotationAxis() const {
    return this->rotationAxis;
}

const float SceneObj::getRotationAngle() const {
    return this->rotationAngle;
}

const Vector &SceneObj::getScaling() const {
    return this->scaling;
}

void SceneObj::setScaling(const Vector &scaling) {
    this->scaling = scaling;
    this->scalingTarget = this->scaling.X;
}

void SceneObj::computeBoundingBox() {
    std::vector<Vertex> vertices = this->getModel()->getVertices();
    //Camera::getInstance().apply();
    
    BoundingBox boundingBox;
    boundingBox.getMax().X = boundingBox.getMin().X = vertices[0].position.X;
    boundingBox.getMax().Y = boundingBox.getMin().Y = vertices[0].position.Y;
    boundingBox.getMax().Z = boundingBox.getMin().Z = vertices[0].position.Z;
    
    for (int i = 0; i < vertices.size(); i++) {
        Vector position = vertices[i].position;
        
        if (boundingBox.getMin().X > position.X) boundingBox.getMin().X = position.X;
        if (boundingBox.getMin().Y > position.Y) boundingBox.getMin().Y = position.Y;
        if (boundingBox.getMin().Z > position.Z) boundingBox.getMin().Z = position.Z;
        
        if (boundingBox.getMax().X < position.X) boundingBox.getMax().X = position.X;
        if (boundingBox.getMax().Y < position.Y) boundingBox.getMax().Y = position.Y;
        if (boundingBox.getMax().Z < position.Z) boundingBox.getMax().Z = position.Z;
    }
    
    this->getModel()->setBoundingBox(boundingBox);
}

void SceneObj::scaleTo(float scaling) {
    if (scaling < 0.0) {
        scaling = 0.0;
    }
    this->scalingTarget = scaling;
}

void SceneObj::translateTo(Vector &translation) {
    this->translationTarget = translation;
}

bool SceneObj::needsTranslationUpdate() {
    if (this->translationTarget.X != this->translation.X) {
        return true;
    }
    if (this->translationTarget.Y != this->translation.Y) {
        return true;
    }
    if (this->translationTarget.Z != this->translation.Z) {
        return true;
    }
    
    return false;
}

void SceneObj::update(float delta) {
    static float scalingPerMilisecond = 1 / 1000;
    
    if (this->scaling.X != this->scalingTarget) {
        float scalingFactor = scalingPerMilisecond * delta;
        if (this->scaling.X > this->scalingTarget) {
            scalingFactor *= -1;
        }
        float newScaling = this->scaling.X + scalingFactor;
        if (newScaling < this->scalingTarget || newScaling > this->scalingTarget) {
            newScaling = scalingTarget;
        }
        this->scaling.X = newScaling;
        this->scaling.Y = newScaling;
        this->scaling.Z = newScaling;
    }
    
    if (this->needsTranslationUpdate()) {
        //float rightDirection = this->translationTarget.X < this->translation.X ? : -1.0
    }
}
