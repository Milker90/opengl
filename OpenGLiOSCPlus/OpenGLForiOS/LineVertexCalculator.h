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
#include <OpenGLES/gltypes.h>

class LineVertexCalculator {
    
public:
    /**
     
     已知一个矩形的中心点，方向，长度，宽度，计算此矩形的四个顶点的坐标
     
     注意：返回结果无需释放，此方法非线程安全
     
     @param center <#center description#>
     @param dir <#dir description#>
     @param height <#height description#>
     @param width <#width description#>
     @return 返回一个数组，包含四个顶点，顺序依次为LT,RT,LB,RB
     */
    static Vector3f* calcluateVertexsForCenter(Vector3f center
                                               ,Vector3f dir
                                               ,float height
                                               ,float width);
    
    /**
     
     已经一条线段的起点、终点、宽度，计算出此线段栅格化对应的矩形的四个顶点的坐标
     
     注意：返回结果无需释放，此方法非线程安全
     
     @param glStart   起点坐标
     @param glTo      终点坐标
     @param lineWidth 线段宽度
     @return 返回一个数组，包含四个顶点，顺序依次为LT,RT,LB,RB
     */
    static Vector3f* calculateVertexsForRectangle(Vector3f *glStart
                                                  ,Vector3f * glTo
                                                  ,float lineWidth);
    
    /**
     
     已经一段圆弧的圆心，起点，终点，计算出构成的扇形多边形

     @param from <#from description#>
     @param to <#to description#>
     @param center <#center description#>
     @param vertices 返回的结果，需要手动释放
     @param indices 返回的结果，需要手动释放
     @param indexCount 返回的结果
     */
    static void verticesForRound(glm::Vector3f from ,
                                 glm::Vector3f to ,
                                 glm::Vector3f center,
                                 GLfloat * & vertices,
                                 GLushort * & indices,
                                 int & indexCount);
    
};


#endif
