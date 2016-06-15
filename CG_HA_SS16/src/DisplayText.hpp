//
//  DisplayText.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef DisplayText_hpp
#define DisplayText_hpp

#include <stdio.h>
#include <iostream>
#include <GLUT/GLUT.h>

class DisplayText {
    
public:
    void displayText( float x, float y, int r, int g, int b, const char *string );
};
#endif /* DisplayText_hpp */
