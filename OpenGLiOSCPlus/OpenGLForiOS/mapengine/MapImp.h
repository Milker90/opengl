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
#include "glm.h"
#include "CShader.h"

class MapImp {
    
public:
    MapImp(int contentWidth, int contentHeight, int viewPortWidth, int viewPortHeight);
    
    void draw();
    
private:
    
    void createMultiSampleBuffer();
    
    void setupRenderBuffer();
    
    void destroyRenderAndFrameBuffer();
    
    void loadBaseTexture();
    
    void loadArrowTexture(const char * imagePath);
    
    void loadLine3DTexture(float lineWidth);
    
    glm::Vector3f screen2openGL2(glm::Vector3f coor);
    
    void drawSegment(glm::Vector3f*glStart ,
                             glm::Vector3f*glTo,
                             float lineWidth,
                             GLfloat* color);
    
    void drawAALineFrom(glm::Vector3f start ,
                                glm::Vector3f to ,
                                float width);
    
    void drawSegmentFrom(glm::Vector3f start ,glm::Vector3f to ,float width);
    
    void drawArrowVertexs(glm::Vector3f start ,glm::Vector3f to ,int arrowCount);
    
    void drawArraysWithTexture(glm::Vector3f* array ,int scale);
    
    void drawRound(glm::Vector3f from ,glm::Vector3f  to ,glm::Vector3f center);
    
    void drawArrays(GLfloat*vertices ,GLushort*indices ,int count);
    
    void drawArraysWithColor(glm::Vector3f*array ,GLfloat*color);
    
    void setMVPFor2D(CShader *shader);
    
    void setMVPFor3D(CShader *shader);
    
    void compileShaders();
    
    void switch2D();
    void switch3D();
    
    void drawLineString(glm::Vector3f*points
                                ,int pointCount
                                ,float width
                                ,GLfloat* color);
    
    void drawRoadLineString(glm::Vector3f *points
                                    ,int pointCount
                                    ,float lineWidth
                            ,float borderWidth);
    
private:
    CShader * textureShader;
    CShader * colorShader;
    CShader * cubeShader;
    CShader * aalineShader;
    
    /* The pixel dimensions of the backbuffer */
    GLint mBackingWidth;
    GLint mBackingHeight;
    
    int mContentWidth, mContentHeight;
    
    GLuint sampleFramebuffer,sampleColorRenderbuffer,sampleDepthRenderbuffer;
    
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
    GLuint _depthRenderBuffer;
    
    GLuint _baseTexture;
    GLuint arrowTexture;
    GLuint aaLineTexture;
    
    int arrowWidth, arrowHeight;
    
    GLuint uniformUseMixColor;
    
    GLuint attribPosition;
    GLuint attribTexCoord;
    GLuint uniformTexture;
    
    GLuint _projectionUniform;
    GLuint _modelViewUniform;
    
    
    
    
    GLuint vaoId;
    
    
    
    
    
    
    
    GLuint colorAttributePosition;
    GLuint colorUniformColorLoc;
    
    GLuint cubeVAO, cubeVBO;
    GLuint skyboxTexture;

};

#endif /* MapImp_hpp */
