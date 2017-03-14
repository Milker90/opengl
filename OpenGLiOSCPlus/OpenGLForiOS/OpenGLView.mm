//
//  OpenGLView.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2016/12/23.
//  Copyright © 2016年 lihuafeng. All rights reserved.
//

#import "OpenGLView.h"
#include "map.h"
#include "MapImp.h"

@interface OpenGLView()

-(void)setupLayer;

@end

@implementation OpenGLView


+(Class)layerClass {
    return [CAEAGLLayer class];
}

-(id)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if (self){
        [self setupLayer];
        [self setupContext];
        
        mpMap = wfCreateMap((__bridge void *)_context, self.frame.size.width, self.frame.size.height);
        
            NSString * imagePath = [[NSBundle mainBundle] pathForResource:@"vector_road_arrow" ofType:@"png"];
        
        wfMapSetArrowTexturePath(mpMap, [imagePath cString]);
        
        [self setupRenderBuffer];
        
        [self render:nil];
    }
    
    return self;
}

-(void)dealloc{
    wfDestroyMap(mpMap);
}


-(void)setupLayer{
    _eaglLayer = (CAEAGLLayer*)self.layer;
    
    _eaglLayer.opaque = YES;
    
    _eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO],
                                     kEAGLDrawablePropertyRetainedBacking,
                                     kEAGLColorFormatRGBA8,
                                     kEAGLDrawablePropertyColorFormat,
                                     nil];
}

-(void)setupContext{
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES3;
    _context = [[EAGLContext alloc]initWithAPI:api];
    if (!_context){
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]){
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

-(void)setupRenderBuffer{
    
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];

}

/*
 */


- (void)render:(CADisplayLink*)displayLink{
    wfMapDraw(mpMap);
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

-(CC3Vector)screen2openGL:(CC3Vector*)coor{
    CC3Vector  ret ;
    
    float screenWidth  = self.frame.size.width;
    float screenHeight = self.frame.size.height;
    
    ret.x = (coor->x - screenWidth/2.0f) / (screenWidth / 2.0f);
    ret.y = (coor->y - screenWidth/2.0f) / (screenWidth / 2.0f);
    ret.z = 0;
    
    return ret;
}

-(void)printMT:(kmMat4 *)mat{
    NSLog(@"===============================");
    for (int i = 0 ; i != 4 ; ++i){
        NSString * a = [[NSString alloc]init];
        for (int j = 0 ; j != 4 ; ++j){
            a = [a stringByAppendingFormat:@"%0.4f  ",mat->mat[i*4+j]];
        }
        NSLog(a);
    }
    NSLog(@"===============================");
}


@end
