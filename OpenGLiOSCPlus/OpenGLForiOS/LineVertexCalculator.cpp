//
//  LineDrawer.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/9.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import "LineVertexCalculator.h"
#include <vector>


Vector3f* LineVertexCalculator::calcluateVertexsForCenter(
                                    Vector3f center
                                    ,Vector3f dir
                                    ,float height
                                    ,float width){
    Vector3f dirNormal = glm::normalize(dir);
    
    Vector3f start = center - (dirNormal * height/2.0f);
    Vector3f to    = center + (dirNormal * height/2.0f);
    
    return calculateVertexsForRectangle(&start ,&to ,width);
}



Vector3f* LineVertexCalculator::calculateVertexsForRectangle(Vector3f *glStart
                                           ,Vector3f * glTo
                                           ,float lineWidth){
    Vector3f center = Vector3f((glStart->x + glTo->x)/2.0f, (glStart->y + glTo->y)/2.0f, 0.0f);
    
    Vector3f vectorBA;
    vectorBA.x = glTo->x - center.x;
    vectorBA.y = glTo->y - center.y;
    vectorBA.z = 0;
    
    Vector3f left  = glm::normalize(Vector3f(-vectorBA.y, vectorBA.x, 0)) *
                                            lineWidth/2.0f;
    Vector3f right = glm::normalize(Vector3f(vectorBA.y, -vectorBA.x, 0)) *
                                            lineWidth/2.0f;
    
    Vector3f LTMat, RTMat, LBMat, RBMat;
    
    LTMat = center +  (vectorBA + left);
    RTMat = center +  (vectorBA + right);
    
    LBMat = center - (vectorBA + right);
    RBMat = center - (vectorBA + left);
    
    static Vector3f ret[4];
    ret[0] = LTMat;
    ret[1] = RTMat;
    ret[2] = LBMat;
    ret[3] = RBMat;
    
    return ret;
}

//LT 代表start
//RT 代表end
void LineVertexCalculator::verticesForRound(glm::Vector3f from ,
                                            glm::Vector3f  to ,
                                            glm::Vector3f center,
                                            GLfloat * & vertices,
                                            GLushort * & indices,
                                            int & indexCount){
    Vector3f start = (from - center);
    Vector3f end   = (to - center);
    
    Vector3f startNor = glm::normalize(start);
    Vector3f endNor   = glm::normalize(end);
    
    float startAngle = acosf(startNor.x);
    if (startNor.y < 0) {
        startAngle = M_PI * 2.0f - startAngle;
    }
    
    float endAngle = acosf(endNor.x);
    if (endNor.y < 0){
        endAngle = M_PI * 2.0f - endAngle;
    }
    
    float delta = -endAngle + startAngle;
    if (delta < 0){
        delta += M_PI * 2.0f;
    }
    
    int count = fabs(delta) / (M_PI / 18.0f) + 0.5f;
    std::vector<Vector3f> vertexs(count+2);
    vertexs[0] = center;
    vertexs[1] = from;
    
    for (int i = 1 ;i < count ; ++i){
        float a  = -delta/count * i;//注意方向
        float sa = sinf(a);
        float ca = cosf(a);
        
        float x = start.x * ca - start.y * sa;
        float y = start.x * sa + start.y * ca;
        
        Vector3f newVec = Vector3f(x, y, 0.0f);
        
        Vector3f vertex = (center + newVec);
        
        vertexs[i+1] = vertex;
    }
    
    vertexs[count+1] = to;
    
    int vertexCount = 3*(count+2);
    vertices = new GLfloat[vertexCount];
    for (int i = 0 ; i != count+2 ; ++i){
        Vector3f ver = vertexs[i];
        vertices[i*3+0] = ver.x;
        vertices[i*3+1] = ver.y;
        vertices[i*3+2] = ver.z;
    }
    indexCount = 3*count;
    indices = new GLushort[indexCount];
    for (int i = 0 ; i != count ; ++i){
        indices[i*3+0] = 0;
        indices[i*3+1] = i+1;
        indices[i*3+2] = i+2;
    }
}
