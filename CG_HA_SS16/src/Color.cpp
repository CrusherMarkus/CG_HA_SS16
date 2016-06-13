//
//  Color.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Color.hpp"

Color Color::operator*(const Color& c) const {
    return Color(R * c.R, G * c.G, B * c.B);
}

Color Color::operator*(const float Factor) const {
    return Color(R * Factor, G * Factor, B * Factor);
}

Color Color::operator+(const Color& c) const {
    return Color(R + c.R, G + c.G, B + c.B);
}

Color& Color::operator+=(const Color& c) {
    this->R += c.R;
    this->G += c.G;
    this->B += c.B;
    
    return *this;
}