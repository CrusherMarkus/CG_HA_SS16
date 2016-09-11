//
//  RGBImage.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef RGBImage_hpp
#define RGBImage_hpp

#include <stdio.h>
#include "Color.hpp"

class RGBImage {
public:
    RGBImage(unsigned int width, unsigned height);
    ~RGBImage();
    void setPixelColor(unsigned int x, unsigned y, const Color &c);
    const Color &getPixelColor(unsigned int x, unsigned y) const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    
    bool saveToDisk(const char *filename) const;
    static unsigned char convertColorChannel(float f);
protected:
    Color *image;
    unsigned int height;
    unsigned int width;
    
    static void swap4BytesAndWriteToBuffer(int value, char *buffer);
    static void swap2BytesAndWriteToBuffer(int value, char *buffer);
};

#endif /* RGBImage_hpp */
