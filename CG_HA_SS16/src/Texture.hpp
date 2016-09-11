//
//  Texture.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "RGBImage.hpp"
#include "Texture.hpp"
#include <stdint.h>
#include <assert.h>

class Texture
{
public:
    Texture();
    ~Texture();
    bool LoadFromBMP( const char* Filename );
    void apply() const;
    bool isValid() const;
    const RGBImage* getRGBImage() const;
protected:
    unsigned char* LoadBMP( const char* Filename, unsigned int& width, unsigned int& height );
    RGBImage* createImage( unsigned char* Data, unsigned int width, unsigned int height );
    GLuint m_TextureID;
    RGBImage* m_pImage;
};

#endif /* Texture_hpp */
