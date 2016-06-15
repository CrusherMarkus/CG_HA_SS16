//
//  Model.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 13.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <iostream>
#include "Vector.hpp"
#include "Color.hpp"
#include <string>
#include <map>
#include <vector>
#include <map>
#include "Material.hpp"
#include "ShaderProgram.hpp"
#include "ShaderManager.hpp"
#include "Camera.hpp"
#include "Vertex.hpp"
#include "BoundingBox.hpp"
#include "ObjModel.hpp"
#include "AbstractModel.hpp"
#include "FaceGroup.hpp"

using namespace std;

class Model : public AbstractModel {
protected:
    string name;
    vector<Vertex> vertices;
    Material *materials;
    int materialCount;
    Texture whiteTexture;
    BoundingBox boundingBox;
    bool selected;
    //vector<FaceGroup> faceGroups;
    
public:
    Model(const std::string &name);
    ~Model();
    
    std::string &getName();
    std::vector<Vertex> &getVertices();
    void setVertices(std::vector<Vertex> &vertices);
    void setMaterials(Material *materials, int materialCount);
    const BoundingBox &getBoundingBox();
    void setBoundingBox(const BoundingBox &boundingBox);
    bool isSelected() const;
    void setSelected(bool isSelected);
    
    void draw() const;
    
protected:
    void drawLines() const;
    void drawTriangles() const;
};


#endif /* Model_hpp */
