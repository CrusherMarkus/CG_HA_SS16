//
//  BoundingBox.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 11.09.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include <stdio.h>
#include "Vector.hpp"

class BoundingBox {
private:
    Vector min;
    Vector max;
    
public:
    BoundingBox();
    BoundingBox(const Vector &min, const Vector &max);
    
    Vector &getMin();
    Vector &getMax();
};

#endif /* BoundingBox_hpp */
