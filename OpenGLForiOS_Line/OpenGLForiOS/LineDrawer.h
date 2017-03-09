//
//  LineDrawer.h
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/9.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CC3GLMatrix.h"
#import "CC3Kazmath.h"

@interface LineDrawer : NSObject

+(CC3Vector*)calcluateVertexsForCenter:(CC3Vector)center
                             direction:(CC3Vector)dir
                                height:(float)height
                                 width:(float)width;

+(CC3Vector*)calculateVertexsForRectangleFrom:(CC3Vector *)glStart
                                           To:(CC3Vector *)glTo
                                        width:(float)lineWidth;

@end
