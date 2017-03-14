//
//  LineDrawer.h
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/9.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#ifndef LINE_DRAWER_HEADER_H
#define LINE_DRAWER_HEADER_H


#include "glm.h"

class LineDrawer {
    
public:
    static Vector3f* calcluateVertexsForCenter(Vector3f center
                                        ,Vector3f dir
                                        ,float height
                                        ,float width);
    
    static Vector3f* calculateVertexsForRectangle(Vector3f *glStart
                                               ,Vector3f * glTo
                                               ,float lineWidth);
    
};


#endif
