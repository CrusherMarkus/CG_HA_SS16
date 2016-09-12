//
//  Color.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdio.h>

class Color {
public:
    float R;
    float G;
    float B;
    
    Color() : R(0), G(0), B(0) {}
    Color(float r, float g, float b) : R(r), G(g), B(b) {}
    Color operator*(const Color& c) const;
    Color operator*(const float Factor) const;
    Color operator+(const Color& c) const;
    Color& operator+=(const Color& c);
};

#endif /* Color_hpp */
