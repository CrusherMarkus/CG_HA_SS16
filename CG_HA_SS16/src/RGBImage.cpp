//
//  RGBImage.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 14.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "RGBImage.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

RGBImage::RGBImage(unsigned int width, unsigned int height)
{
    this->m_Width = width;
    this->m_Height = height;
    this->m_Image = new Color[width*height]();
}

void RGBImage::setPixelColor(unsigned int x, unsigned int y,const Color& c)
{
    if( x < width() && y < height() )
    {
        //Setze Pixelfarbe
        m_Image[width()*y+x] = c;
    }
}

const Color& RGBImage::getPixelColor(unsigned int x, unsigned int y) const
{
    if( x < width() && y < height() )
    {
        //Setze Pixelfarbe
        return m_Image[width()*y+x];
    }
    return Color();
}

bool RGBImage::saveToDisk(const char* filename)
{
    std::string filenameComplete = filename;
    filenameComplete.append(".bmp");
    unsigned int headers[16];
    FILE * outfile;
    unsigned int extrabytes;
    unsigned int paddedsize;
    
    extrabytes = 4 - width()%4;
    if(extrabytes == 4)
    {
        extrabytes = 0;
    }
    
    //Die Größe der Bilddaten beträgt näherungsweise (gilt nur für durch 4 teilbare Bildbreiten) biWidth×biHeight×biBitCount/8, also extrabytes damit width()%4==0 gilt bzw. paddedsize%4==0
    paddedsize = width()*height()*3+extrabytes;
    
    headers[0]  = paddedsize + 54;      // bfSize
    headers[1]  = 0;                    // bfReserved (1&2)
    headers[2]  = 54;                   // bfOffbits
    
    headers[3]  = 40;                   // biSize
    headers[4]  = width();              // biWidth
    headers[5]  = height();             // biHeight
    headers[6]  = 1;                    //biPlanes
    headers[7]  = 0;                    //biPlanes
    headers[8]  = 24;                   //biBitCount
    headers[9]  = 0;                    //biBitCount
    
    headers[10]  = 0;                    // biCompression
    headers[11]  = paddedsize;           // biSizeImage
    headers[12]  = 0;                    // biXPelsPerMeter
    headers[13] = 0;                    // biYPelsPerMeter
    headers[14] = 0;                    // biClrUsed
    headers[15] = 0;                    // biClrImportant
    
    outfile = fopen(filenameComplete.c_str(), "wb");
    
    fprintf(outfile, "BM"); // bfType (2Byte)
    
    //Man schreibt einen character pro Zeile um endian probleme zu vermeiden
    //char hat größe von 1Byte also bitShiftet man jeweils um 8 bit
    for (unsigned int n = 0; n <= 5; n++) //(Jeweils 4 Byte)
    {
        fprintf(outfile, "%c", headers[n]);
        fprintf(outfile, "%c", (headers[n]) >> 8);
        fprintf(outfile, "%c", (headers[n]) >> 16);
        fprintf(outfile, "%c", (headers[n]) >> 24);
    }
    
    fprintf(outfile, "%c", headers[6]); // 6&7 2 Byte
    fprintf(outfile, "%c", headers[7]);
    fprintf(outfile, "%c", headers[8]); // 8&7 2 Byte
    fprintf(outfile, "%c", headers[9]);
    
    for (unsigned int n = 10; n <= 15; n++) //Letzten 6 jeweils wieder 4 Byte
    {
        fprintf(outfile, "%c", headers[n]);
        fprintf(outfile, "%c", (headers[n]) >> 8);
        fprintf(outfile, "%c", (headers[n]) >> 16);
        fprintf(outfile, "%c", (headers[n]) >> 24);
    }
    
    // 24 bpp:Die Daten jedes Pixels bestehen aus jeweils einem Byte für den Blau-, Grün- und Rot-Kanal (in dieser Reihenfolge!)
    for (int y = height()-1; y >= 0; y--)
    {
        for (unsigned int x = 0; x < width(); x++)
        {
            //Reihenfolge b,g,r ist so definiert warum auch immer ...
            fprintf(outfile, "%c", convertColorChannel(getPixelColor(x,y).B));
            fprintf(outfile, "%c", convertColorChannel(getPixelColor(x,y).G));
            fprintf(outfile, "%c", convertColorChannel(getPixelColor(x,y).R));
        }
        
        if(extrabytes){
            for(unsigned int n=1; n <= extrabytes; n++){
                fprintf(outfile,"%c",0);
            }
        }
    }
    
    fclose(outfile);
    return true;
}

unsigned int RGBImage::width() const
{
    return m_Width;
}

unsigned int RGBImage::height() const
{
    return m_Height;
}

unsigned char RGBImage::convertColorChannel(float f)
{
    if(f <= 0)
    {
        return 0;
    }
    else if(f >= 1)
    {
        return 255;
    }
    else
    {
        return f*255;
    }
}

RGBImage::~RGBImage()
{
    delete [] m_Image;
}

