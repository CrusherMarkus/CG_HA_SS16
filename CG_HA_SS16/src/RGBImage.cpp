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

using namespace std;

struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint32_t bfReserved;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t bfSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

RGBImage::RGBImage(unsigned int width, unsigned height) {
    this->width = width;
    this->height = height;
    
    this->image = new Color[width * height];
}

RGBImage::~RGBImage() {
    delete [] this->image;
}

void RGBImage::setPixelColor(unsigned int x, unsigned y, const Color &c) {
    if (x >= this->width) {
        x = this->width - 1;
    }
    if (x >= this->height) {
        y = this->height - 1;
    }
    
    this->image[x + y * this->width] = c;
}

const Color &RGBImage::getPixelColor(unsigned int x, unsigned y) const {
    if (x >= this->width) {
        x = this->width - 1;
    }
    if (x >= this->height) {
        y = this->height - 1;
    }
    
    return this->image[x + y * this->width];
}

unsigned int RGBImage::getWidth() const {
    return this->width;
}

unsigned int RGBImage::getHeight() const {
    return this->height;
}

bool RGBImage::saveToDisk(const char *filename) const {
    ofstream outputFile;
    char buffer[128];
    
    outputFile.open(filename, ofstream::out | ofstream::binary);
    if (!outputFile) {
        return false;
    }
    
    BITMAPFILEHEADER bmpFileHeader;
    bmpFileHeader.bfType = 0x4d42;
    bmpFileHeader.bfSize = 14 + 40 + (this->width * this->height * 3);
    bmpFileHeader.bfReserved = 0;
    bmpFileHeader.bfOffBits = 14 + 40;
    
    BITMAPINFOHEADER bmpInfoHeader;
    bmpInfoHeader.bfSize = 40;
    bmpInfoHeader.biWidth = this->width;
    bmpInfoHeader.biHeight = this->height;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24;
    bmpInfoHeader.biCompression = 0;
    bmpInfoHeader.biSizeImage = this->width * this->height * 3;
    bmpInfoHeader.biXPelsPerMeter = 0;
    bmpInfoHeader.biYPelsPerMeter = 0;
    bmpInfoHeader.biClrUsed = 0;
    bmpInfoHeader.biClrImportant = 0;
    
    outputFile.write((char *)&bmpFileHeader.bfType, sizeof(bmpFileHeader.bfType));
    outputFile.write((char *)&bmpFileHeader.bfSize, sizeof(bmpFileHeader.bfSize));
    outputFile.write((char *)&bmpFileHeader.bfReserved, sizeof(bmpFileHeader.bfReserved));
    outputFile.write((char *)&bmpFileHeader.bfOffBits, sizeof(bmpFileHeader.bfOffBits));
    
    //outputFile.write((char *)&bmpInfoHeader, sizeof(BITMAPFILEHEADER));
    outputFile.write((char *)&bmpInfoHeader, sizeof(BITMAPINFOHEADER));
    
    int padSize = (4 - 3 * this->width % 4) % 4;
    
    // save bitmap upside down (default)
    for (int y = this->height - 1; y >= 0; y--) {
        for (int x = 0; x < this->width; x++) {
            unsigned char pixel[3];
            Color color = this->getPixelColor(x, y);
            
            pixel[0] = RGBImage::convertColorChannel(color.B);
            pixel[1] = RGBImage::convertColorChannel(color.G);
            pixel[2] = RGBImage::convertColorChannel(color.R);
            
            outputFile.write((char *)&pixel, 3);
        }
        
        for (int i = 0; i < padSize; i++) {
            outputFile.write(0x00, 1);
        }
    }
    
    outputFile.flush();
    outputFile.close();
    
    return true;
}

unsigned char RGBImage::convertColorChannel(float f) {
    if(f < 0.0f) {
        f = 0.0f;
    } else if (f > 1.0) {
        f = 1.0f;
    }
    
    return f * 255;
}

void RGBImage::swap2BytesAndWriteToBuffer(int value, char *buffer) {
    buffer[0] = (value) & 0xff;
    buffer[1] = (value >> 0x08) & 0xff;
}

void RGBImage::swap4BytesAndWriteToBuffer(int value, char *buffer) {
    buffer[0] = (value) & 0xff;
    buffer[1] = (value >> 0x08) & 0xff;
    buffer[2] = (value >> 0x10) & 0xff;
    buffer[3] = (value >> 0x18) & 0xff;
}
