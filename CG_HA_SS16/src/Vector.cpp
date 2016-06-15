//
//  Vector.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Vector.hpp"
#include <math.h>

Vector::Vector() {
    this->X = 0.0;
    this->Y = 0.0;
    this->Z = 0.0;
}

Vector::Vector(float x, float y, float z) {
    this->X = x;
    this->Y = y;
    this->Z = z;
}

/*
 *  Skalarprodukt
 */
float Vector::dot(const Vector &v) const {
    float dot;
    
    dot = (this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z);
    
    return dot;
}

/*
 *  Kreuzprodukt
 */
Vector Vector::cross(const Vector& v) const {
    Vector crossResult;
    
    crossResult.X = this->Y * v.Z - this->Z * v.Y;
    crossResult.Y = this->Z * v.X - this->X * v.Z;
    crossResult.Z = this->X * v.Y - this->Y * v.X;
    
    return crossResult;
}

/*
 *  Addition
 */
Vector Vector::operator+(const Vector& v) const {
    Vector additionResult;
    
    additionResult.X = this->X + v.X;
    additionResult.Y = this->Y + v.Y;
    additionResult.Z = this->Z + v.Z;
    
    return additionResult;
}

/*
 *  Subtraktion
 */
Vector Vector::operator-(const Vector& v) const {
    Vector substractionResult;
    
    substractionResult.X = this->X - v.X;
    substractionResult.Y = this->Y - v.Y;
    substractionResult.Z = this->Z - v.Z;
    
    return substractionResult;
}

/*
 *  Additionszuweisung
 */
Vector &Vector::operator+=(const Vector& v) {
    this->X += v.X;
    this->Y += v.Y;
    this->Z += v.Z;
    
    return *this;
}

/*
 *  Multiplikation
 */
Vector Vector::operator*(float c) const {
    Vector multiplicationResult;
    
    multiplicationResult.X = this->X * c;
    multiplicationResult.Y = this->Y * c;
    multiplicationResult.Z = this->Z * c;
    
    return multiplicationResult;
}

/*
 *  Negierung
 */
Vector Vector::operator-() const {
    Vector negatedVector;
    
    negatedVector.X = this->X * -1;
    negatedVector.Y = this->Y * -1;
    negatedVector.Z = this->Z * -1;
    
    return negatedVector;
}

/*
 *  Normalisierung
 */
Vector &Vector::normalize() {
    *this = *this * (1 / this->length()); // Vektor * (1 / Länge des Vektors)
    
    return *this;
}

/*
 *  Länge
 */
float Vector::length() const {
    return sqrt(this->lengthSquared());
}

/*
 *  Quadratische Länge
 */
float Vector::lengthSquared() const {
    float lengthSquared = pow(this->X, 2) + pow(this->Y, 2) + pow(this->Z, 2);
    
    return lengthSquared;
}

/*
 *  Reflexion an der Oberfläche
 */
Vector Vector::reflection(const Vector &normal) const {
    Vector reflectionResult;
    
    reflectionResult = *this - normal * 2.0f * this->dot(normal); // ve - n * 2 * dot(ve, n)
    
    return reflectionResult;
}

/*
 *  Strahl-Dreieck-Kollision
 *  Strahl, abhängig von Ursprung und Richtung
 *
 *
 */
bool Vector::triangleIntersection(const Vector &d, const Vector &a, const Vector &b, const Vector &c, float &s) const {
    Vector normal = (b - a).cross(c - a).normalize(); // Normalenvektor der Ebene
    
    float distance = normal.dot(a);     // Distanz Ursprung zur Ebene = Skalarprodukt / Projektion von Vektor a auf Normale
    float no = normal.dot(*this);
    float nd = normal.dot(d);
    
    s = (distance - no) / nd;           //Skalierung von Vektor
    
    if (s < 0) {
        return false;
    }
    
    Vector p = *this + (d * s);
    
    //Dreiecke aufspannen
    float abc = (b - a).cross(c - a).length() / 2;
    float abp = (b - a).cross(p - a).length() / 2;
    float acp = (c - a).cross(p - a).length() / 2;
    float bcp = (c - b).cross(p - b).length() / 2;
    
    static float epsilon = 1e-6f;       //Toleranz
    
    //Vergleich der Flächeninhalte
    float result = abc - abp - acp - bcp;
    
    return result > -epsilon && result < epsilon;
}