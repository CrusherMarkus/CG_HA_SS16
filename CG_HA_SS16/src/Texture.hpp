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

class Texture
{
public:
    Texture();
    ~Texture();
    bool LoadFromBMP( const char* Filename );
    void apply() const;
    bool isValid() const;
protected:
    unsigned char* LoadBMP( const char* Filename, unsigned int& width, unsigned int& height );
    GLuint m_TextureID;
    
};

#endif /* Texture_hpp */
