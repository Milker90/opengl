//
//  LineDrawer.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/9.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import "LineDrawer.h"

@implementation LineDrawer

+(CC3Vector*)calcluateVertexsForCenter:(CC3Vector)center
                             direction:(CC3Vector)dir
                                height:(float)height
                                 width:(float)width{
    CC3Vector dirNormal = CC3VectorNormalize(dir);
    
    CC3Vector start = CC3VectorDifference(center, CC3VectorScaleUniform(dirNormal, height/2.0f));
    CC3Vector to    = CC3VectorAdd(center, CC3VectorScaleUniform(dirNormal, height/2.0f));
    
    return [[self class] calculateVertexsForRectangleFrom:&start To:&to width:width];
}

+(CC3Vector*)calculateVertexsForRectangleFrom:(CC3Vector *)glStart
                                           To:(CC3Vector *)glTo
                                        width:(float)lineWidth{
    CC3Vector center = CC3VectorMake((glStart->x + glTo->x)/2.0f, (glStart->y + glTo->y)/2.0f, 0.0f);
    
    CC3Vector vectorBA;
    vectorBA.x = glTo->x - center.x;
    vectorBA.y = glTo->y - center.y;
    vectorBA.z = 0;
    
    CC3Vector left  = CC3VectorScaleUniform( CC3VectorNormalize(CC3VectorMake(-vectorBA.y, vectorBA.x, 0)),
                                            lineWidth/2.0f);
    CC3Vector right = CC3VectorScaleUniform( CC3VectorNormalize(CC3VectorMake(vectorBA.y, -vectorBA.x, 0)),
                                            lineWidth/2.0f);
    
    CC3Vector LTMat, RTMat, LBMat, RBMat;
    
    LTMat = CC3VectorAdd(center,  CC3VectorAdd(vectorBA, left));
    RTMat = CC3VectorAdd(center,  CC3VectorAdd(vectorBA, right));
    
    LBMat = CC3VectorDifference(center, (CC3VectorAdd(vectorBA, right)));
    RBMat = CC3VectorDifference(center, (CC3VectorAdd(vectorBA, left)));
    
    static CC3Vector ret[4];
    ret[0] = LTMat;
    ret[1] = RTMat;
    ret[2] = LBMat;
    ret[3] = RBMat;
    
    return ret;
}

@end
