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

class RGBImage
{
public:
    RGBImage(unsigned int width, unsigned int height);
    virtual ~RGBImage();
    void setPixelColor(unsigned int x, unsigned int y,const Color& c);
    const Color& getPixelColor(unsigned int x, unsigned int y) const;
    bool saveToDisk(const char* filename);
    unsigned int width() const;
    unsigned int height() const;
    
    static unsigned char convertColorChannel(float f);
protected:
    Color *m_Image;
    unsigned int m_Width;
    unsigned int m_Height;
};

#endif /* RGBImage_hpp */
