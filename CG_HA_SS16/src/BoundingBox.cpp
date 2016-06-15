//
//  BoundingBox.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{
}
BoundingBox::BoundingBox( const Vector& min, const Vector& max) : Min(min), Max(max)
{
}