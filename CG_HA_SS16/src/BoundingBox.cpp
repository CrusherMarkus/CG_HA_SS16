//
//  BoundingBox.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
    
}

BoundingBox::BoundingBox(const Vector &min, const Vector &max) {
    this->min = min;
    this->max = max;
}

Vector &BoundingBox::getMin() {
    return this->min;
}

Vector &BoundingBox::getMax() {
    return this->max;
}