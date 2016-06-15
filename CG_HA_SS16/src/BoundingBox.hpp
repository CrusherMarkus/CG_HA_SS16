//
//  BoundingBox.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include <stdio.h>
#include "Vector.hpp"

class BoundingBox {
public:
    BoundingBox();
    BoundingBox(const Vector& min, const Vector &max);
    Vector Min;
    Vector Max;
};

#endif /* BoundingBox_hpp */
