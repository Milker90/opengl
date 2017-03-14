//
//  LineDrawer.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/9.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import "LineDrawer.h"



Vector3f* LineDrawer::calcluateVertexsForCenter(Vector3f center
                                    ,Vector3f dir
                                    ,float height
                                    ,float width){
    Vector3f dirNormal = glm::normalize(dir);
    
    Vector3f start = (center - (dirNormal * height/2.0f));
    Vector3f to    = (center + (dirNormal * height/2.0f));
    
    return calculateVertexsForRectangle(&start ,&to ,width);
}

Vector3f* LineDrawer::calculateVertexsForRectangle(Vector3f *glStart
                                           ,Vector3f * glTo
                                           ,float lineWidth){
    Vector3f center = Vector3f((glStart->x + glTo->x)/2.0f, (glStart->y + glTo->y)/2.0f, 0.0f);
    
    Vector3f vectorBA;
    vectorBA.x = glTo->x - center.x;
    vectorBA.y = glTo->y - center.y;
    vectorBA.z = 0;
    
    Vector3f left  = ( glm::normalize(Vector3f(-vectorBA.y, vectorBA.x, 0)) *
                                            lineWidth/2.0f);
    Vector3f right = ( glm::normalize(Vector3f(vectorBA.y, -vectorBA.x, 0)) *
                                            lineWidth/2.0f);
    
    Vector3f LTMat, RTMat, LBMat, RBMat;
    
    LTMat = (center +  (vectorBA + left));
    RTMat = (center +  (vectorBA + right));
    
    LBMat = (center - ((vectorBA + right)));
    RBMat = (center - ((vectorBA + left)));
    
    static Vector3f ret[4];
    ret[0] = LTMat;
    ret[1] = RTMat;
    ret[2] = LBMat;
    ret[3] = RBMat;
    
    return ret;
}


