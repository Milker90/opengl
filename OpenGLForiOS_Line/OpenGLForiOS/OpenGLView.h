//
//  OpenGLView.h
//  OpenGLForiOS
//
//  Created by lihuafeng on 2016/12/23.
//  Copyright © 2016年 lihuafeng. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#import "CC3GLMatrix.h"
#import "CC3Kazmath.h"
#import "CShader.h"

@interface OpenGLView : UIView {
    CAEAGLLayer * _eaglLayer;
    EAGLContext * _context;
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
    
    GLuint attribPosition;
    GLuint attribTexCoord;
    GLuint uniformTexture;
    GLuint uniformUseMixColor;
    
    GLuint _projectionUniform;
    GLuint _modelViewUniform;
    
    float _currentRotation;
    
    GLuint _depthRenderBuffer;
    
    GLuint vaoId;
    
    GLuint _baseTexture;
    GLuint arrowTexture;
    GLuint aaLineTexture;
    
    int arrowWidth, arrowHeight;
    
    CShader * textureShader;
    CShader * colorShader;
    CShader * cubeShader;
    CShader * aalineShader;
    
    GLuint colorAttributePosition;
    GLuint colorUniformColorLoc;
    
    GLuint cubeVAO, cubeVBO;
    GLuint skyboxTexture;
    
    GLuint sampleFramebuffer,sampleColorRenderbuffer,sampleDepthRenderbuffer;
    
    /* The pixel dimensions of the backbuffer */
    GLint mBackingWidth;
    GLint mBackingHeight;
}

-(void)switch3D;
-(void)switch2D;

-(void)move:(int)offsetX y:(int)offsetY;

@end
