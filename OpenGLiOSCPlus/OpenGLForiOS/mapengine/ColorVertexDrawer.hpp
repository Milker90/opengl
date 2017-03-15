//
//  ColorVertexDrawer.hpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#ifndef ColorVertexDrawer_hpp
#define ColorVertexDrawer_hpp

#include <stdio.h>
#include "CShader.h"
#include "glm.h"

class ColorVertexDrawer{
    
public:
    ColorVertexDrawer();
    ~ColorVertexDrawer();
    
    void useProgram();
    
    void setMVP(glm::Matrix4f mvp);
    
    void setColor(GLfloat *color);
    
    void drawArrays(GLfloat*vertices ,GLushort*indices ,int indexCount);
    
    void drawRectangleWithColor(glm::Vector3f* array ,GLfloat*color);
    
private:
    CShader *colorShader;
    
    int positionLocation;
    int colorLocation;
    int mvpLocation;
};

#endif
