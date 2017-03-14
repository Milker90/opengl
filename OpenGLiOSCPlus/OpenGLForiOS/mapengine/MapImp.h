//
//  MapImp.hpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#ifndef MapImp_hpp
#define MapImp_hpp

#include <stdio.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

class MapImp {
    
public:
    MapImp(int width, int height);
    
    void draw();
    
private:
    
    void createMultiSampleBuffer();
    
    void setupRenderBuffer();
    
    void destroyRenderAndFrameBuffer();
    
    /* The pixel dimensions of the backbuffer */
    GLint mBackingWidth;
    GLint mBackingHeight;
    
    GLuint sampleFramebuffer,sampleColorRenderbuffer,sampleDepthRenderbuffer;
    
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
    GLuint _depthRenderBuffer;
    
};

#endif /* MapImp_hpp */
