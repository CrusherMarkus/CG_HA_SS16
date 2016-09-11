//
//  Model.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 17.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "AbstractModel.hpp"
#include "Vertex.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "BoundingBox.hpp"
#include "FaceGroup.hpp"
#include "ShaderProgram.hpp"
#include "ShaderManager.hpp"


#include <vector>

class Vertex;

class Model : public AbstractModel {
protected:
    std::string name;
    std::vector<Vertex> vertices;
    Material *materials;
    int materialCount;
    Texture whiteTexture;
    BoundingBox boundingBox;
    bool selected;
    std::vector<FaceGroup> faceGroups;
    
    ShaderProgram *shader;
    
public:
    Model();
    ~Model();
    
    std::string &getName();
    std::vector<Vertex> &getVertices();
    void setVertices(std::vector<Vertex> &vertices);
    void setMaterials(Material *materials, int materialCount);
    const BoundingBox &getBoundingBox();
    void setBoundingBox(const BoundingBox &boundingBox);
    
    void draw() const;
    
protected:
    void drawLines() const;
    void drawTriangles() const;
};
#endif /* Model_hpp */
