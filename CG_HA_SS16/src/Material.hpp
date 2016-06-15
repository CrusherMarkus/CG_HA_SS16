//
//  Material.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <iostream>
#include "Vector.hpp"
#include "Color.hpp"
#include "Texture.hpp"

class Material
{
public:
    Material( Vector kd, Vector ks, Vector ka, float ns, std::string name );
    Material();
    ~Material();
    const Color& getDiffuseColor() const;
    const Texture &getDiffuseTexture() const;
    const Color& getSpecularColor() const;
    const Color& getAmbientColor() const;
    float getSpecularExponent() const;
    const std::string& getName() const;
    
    void setDiffuseColor( const Color& color);
    void setSpecularColor( const Color& color);
    void setAmbientColor( const Color& color);
    void setSpecularExponent( const float exp);
    void setName( const std::string& name);
    void setDiffuseTexture( const char* Filename);
    
protected:
    Color m_DiffuseColor;
    Color m_SpecularColor;
    Color m_AmbientColor;
    Texture m_DiffuseTexture;
    float m_SpecularExp;
    std::string m_Name;
    
};
#endif /* Material_hpp */
