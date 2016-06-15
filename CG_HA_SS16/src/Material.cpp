//
//  Material.cpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#include "Material.hpp"

Material::Material( Vector kd, Vector ks, Vector ka, float ns, std::string name )
{
    
}

Material::Material()
{
}

Material::~Material()
{
    
}

const Color& Material::getDiffuseColor() const
{
    return m_DiffuseColor;
}

const Color& Material::getSpecularColor() const
{
    return m_SpecularColor;
}

const Color& Material::getAmbientColor() const
{
    return m_AmbientColor;
}

float Material::getSpecularExponent() const
{
    return m_SpecularExp;
}

const std::string& Material::getName() const
{
    return m_Name;
}

void Material::setDiffuseColor( const Color& color)
{
    m_DiffuseColor = color;
}

const Texture &Material::getDiffuseTexture() const {
    return this->m_DiffuseTexture;
}

void Material::setSpecularColor( const Color& color)
{
    m_SpecularColor = color;
}

void Material::setAmbientColor( const Color& color)
{
    m_AmbientColor = color;
}

void Material::setSpecularExponent( const float exp)
{
    m_SpecularExp = exp;
}

void Material::setName( const std::string& name)
{
    m_Name = name;
}

void Material::setDiffuseTexture( const char* Filename)
{
    m_DiffuseTexture.LoadFromBMP(Filename);
}



