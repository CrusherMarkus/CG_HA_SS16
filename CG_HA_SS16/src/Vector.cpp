//
//  Vector.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vector.hpp"
#include <math.h>

float Vector::dot(const Vector &v) const {
    return X * v.X + Y * v.Y + Z * v.Z;
}

Vector Vector::cross(const Vector &v) const {
    return Vector(Y * v.Z - Z * v.Y,
                  Z * v.X - X * v.Z,
                  X * v.Y - Y * v.X);
}

Vector Vector::operator+(const Vector &v) const {
    return Vector(X + v.X, Y + v.Y, Z + v.Z);
}

Vector Vector::operator-(const Vector &v) const {
    return Vector(X - v.X, Y - v.Y, Z - v.Z);
}

Vector& Vector::operator+=(const Vector &v) {
    this->X += v.X;
    this->Y += v.Y;
    this->Z += v.Z;
    
    return *this;
}

Vector Vector::operator*(float c) const {
    return Vector(X * c, Y * c, Z * c);
}

Vector Vector::operator-() const {
    return Vector(0 - X, 0 - Y, 0 - Z);
}

Vector& Vector::normalize() {
    float l = 1;
    
    if(this->length() != 0)
        l = 1 / this->length();
    
    this->X *= l;
    this->Y *= l;
    this->Z *= l;
    
    return *this;
}

float Vector::length() const {
    return sqrtf(this->lengthSquared());
}

float Vector::lengthSquared() const {
    return X * X + Y * Y + Z * Z;
}

// normal -> Normalform der Eben, an der Reflektiert wird.
Vector Vector::reflection(const Vector& normal) const {
    return *this - normal * 2 * (normal.dot(*this));
}

bool Vector::triangleIntersection(const Vector& d, const Vector& a, const Vector& b,
                                  const Vector& c, float& s) const {
    // 1. get intersection with plane
    Vector n = ((b - a).cross(c - a)).normalize();
    
    if(d.dot(n) == 0)
        return false;
    
    // use a instead of p
    s = (a.dot(n) - n.dot(*this)) / n.dot(d);
    
    if(s <= 0)
        return false;
    
    // 2. get intersection in triangle
    Vector p = *this + (d * s);
    
    float tABC = ((b - a).cross(c - a)).length() / 2;
    float tABP = ((b - a).cross(p - a)).length() / 2;
    float tACP = ((c - a).cross(p - a)).length() / 2;
    float tBCP = ((c - b).cross(p - b)).length() / 2;

    float epsilon = 1e-6;
    float sum = tABC - (tABP + tACP + tBCP);
    
    if(sum > -epsilon && sum < epsilon)
        return true;
    
    return false;
}



