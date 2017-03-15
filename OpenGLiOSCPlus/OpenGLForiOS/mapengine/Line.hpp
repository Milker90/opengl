//
//  Line.hpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include "glm.h"
#include <OpenGLES/gltypes.h>


class ColorVertexDrawer;
class MapImp;

class Line{
    
public:
    Line(MapImp * map, ColorVertexDrawer * colorDrawer);
    ~Line();
    
    void draw(glm::Vector3f*points
              ,int pointCount
              ,float width
              ,GLfloat* color);
    
    void drawSegment(glm::Vector3f*glStart ,
                     glm::Vector3f*glTo,
                     float lineWidth,
                     GLfloat* color);
    
private:
    void drawRound(glm::Vector3f from ,glm::Vector3f  to ,glm::Vector3f center);
    
    
    
private:
    ColorVertexDrawer *mColorDrawer;
    MapImp * mMap;
};

#endif /* Line_hpp */
