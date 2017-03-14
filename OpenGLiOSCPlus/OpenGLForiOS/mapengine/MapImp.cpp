//
//  MapImp.cpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#include "MapImp.h"
#include <stdlib.h>
#include <math.h>
#include "SOIL.h"
#include <vector>
#include "LineDrawer.h"
#include "ShaderGLSL.h"

using namespace glm;

#define VERTEX_POS_SIZE      3
#define VERTEX_COLOR_SIZE    2

#define VERTEX_STRIDE        (sizeof(GL_FLOAT) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE))


static const Vector3f mix0 = {0.0f, -1.0f,  1.0f};
static const Vector3f mix1 = {0.0f, 0.0f,   1.0f};
static const Vector3f mix2 = {1.0f, 0.0f,   1.0f};
static const Vector3f mix3 = {1.0f, 1.0f,   1.0f};
static const Vector3f mix4 = {0.0f, -1.0f,  -1.0f};
static const Vector3f mix5 = {0.0f, 0.0f,   -1.0f};
static const Vector3f mix6 = {1.0f, 0.0f,   -1.0f};
static const Vector3f mix7 = {1.0f, 1.0f,   -1.0f};


GLubyte * createTextureLine3D(int lineWidth);

unsigned int nextPowerOfTwo(unsigned int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

MapImp::MapImp(int contentWidth, int contentHeight, int viewPortWidth, int viewPortHeight):
colorShader(NULL),
textureShader(NULL),
aalineShader(NULL),
cubeShader(NULL){
    mContentWidth = contentWidth;
    mContentHeight = contentHeight;
    
    mBackingWidth  = viewPortWidth;
    mBackingHeight = viewPortHeight;
    
    destroyRenderAndFrameBuffer();
    
    setupRenderBuffer();
}

MapImp::~MapImp(){
    if (colorShader){
        delete colorShader;
    }
    
    if (textureShader){
        delete  textureShader;
    }
    
    if (aalineShader){
        delete aalineShader;
    }
    
    if (cubeShader){
        delete cubeShader;
    }
}

void MapImp::createMultiSampleBuffer(){
    glGenFramebuffers(1, &sampleFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, sampleFramebuffer);
    
    glGenRenderbuffers(1, &sampleColorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, sampleColorRenderbuffer);
    
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, mContentWidth, mContentHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, sampleColorRenderbuffer);
    
    glGenRenderbuffers(1, &sampleDepthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, sampleDepthRenderbuffer);
    
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT16, mContentWidth, mContentHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, sampleDepthRenderbuffer);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        
    }
}

void MapImp::setupRenderBuffer(){
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mContentWidth, mContentHeight);
    
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    
    glGenFramebuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

void MapImp::destroyRenderAndFrameBuffer(){
    glDeleteFramebuffers(1, &_frameBuffer);
    _frameBuffer = 0;
    glDeleteRenderbuffers(1, &_colorRenderBuffer);
    _colorRenderBuffer = 0;
}

glm::Vector3f MapImp::screen2openGL2(glm::Vector3f coor){
    Vector3f  ret ;
    
    float screenWidth  = mBackingWidth;
    float screenHeight = mBackingHeight;
    
    ret.x = (coor.x - screenWidth/2.0f) / (screenWidth / 2.0f);
    ret.y = (coor.y - screenWidth/2.0f) / (screenWidth / 2.0f);
    ret.z = 0;
    
    return ret;
}

void MapImp::draw(){
    //        glEnable(GL_DEPTH_TEST);
    glClearColor(0.95f, 0.95f, 0.91f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //        glEnable(GL_MULTISAMPLE);
    
    compileShaders();
    
    loadBaseTexture();
    loadArrowTexture(mArrowPath);
    
#ifdef USE_MULTI_SAMPLE
    //    glBindFramebuffer(GL_FRAMEBUFFER, sampleFramebuffer);
    //    glBindRenderbuffer(GL_RENDERBUFFER, sampleColorRenderbuffer);
#endif
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, mBackingWidth, mBackingHeight);
    
    colorShader->useProgram();
    
    glm::Vector3f start, to;
    start.x = 100;
    start.y = 70;
    start.z = 0;
    
    to.x = 300.0f;
    to.y = 90;
    to.z = 0;
    
    float width = 20.0f;
    
    drawSegmentFrom(start ,to ,width);
    
    GLfloat color[4] = {1,0,0,0.5f};
    
    {
        Vector3f s = screen2openGL2(Vector3f(100, 150, 0));
        Vector3f e = screen2openGL2(Vector3f(300,170, 0));
        float lineWidth = 40.0f / (mBackingWidth / 2.0f);
        drawSegment(&s ,&e ,lineWidth ,color);
    }
    
    loadLine3DTexture(40.0f);
    glBindTexture(GL_TEXTURE_2D, aaLineTexture);
    
    drawAALineFrom(Vector3f(100, 150, 0) ,Vector3f(300, 170, 0) ,40.0f);
    
    drawAALineFrom(Vector3f(100, 70, 0) ,Vector3f(300, 90, 0) ,40.0f);
    
    drawSegmentFrom(Vector3f(20, 30, 0) ,Vector3f(350, 30, 0) ,width);
    
    drawSegmentFrom(Vector3f(30, 70, 0) ,Vector3f(30, 300, 0) ,width);
    
    Vector3f lines[9];
    lines[0] = Vector3f(100, 150, 0);
    lines[1] = Vector3f(100, 250, 0);
    lines[2] = Vector3f(200, 250, 0);
    lines[3] = Vector3f(200, 350, 0);
    lines[4] = Vector3f(250, 300, 0);
    lines[5] = Vector3f(300, 350, 0);
    lines[6] = Vector3f(300, 200, 0);
    lines[7] = Vector3f(350, 150, 0);
    lines[8] = Vector3f(150, 150, 0);
    
    drawRoadLineString(lines ,9 ,width ,1.0f);
    
    
#ifdef USE_MULTI_SAMPLE
    //    glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, _frameBuffer);
    //    glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, sampleFramebuffer);
    //
    //
    //    // opengl 2.0
    //    //    glResolveMultisampleFramebufferAPPLE();
    //    //    const GLenum discards[]  = {GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT};
    //    //    glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE,2,discards);
    //
    //    // opengl 3.0
    //    glInvalidateFramebuffer(GL_READ_FRAMEBUFFER, 1, (GLenum[]){GL_DEPTH_ATTACHMENT});
    //
    //    // Copy the read fbo(multisampled framebuffer) to the draw fbo(single-sampled framebuffer)
    //    glBlitFramebuffer(0, 0, mBackingWidth, mBackingHeight, 0, 0, mBackingWidth, mBackingHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    //
    //    glInvalidateFramebuffer(GL_READ_FRAMEBUFFER, 1, (GLenum[]){GL_COLOR_ATTACHMENT0});
    //
    //    //end
    //    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
#endif
}

void MapImp::drawSegment(glm::Vector3f*glStart ,
                         glm::Vector3f*glTo,
                         float lineWidth,
                         GLfloat* color){
    
    
    Vector3f * array = LineDrawer::calculateVertexsForRectangle(glStart ,glTo ,lineWidth);
    drawArraysWithColor(array ,color);
    glUniform4fv(colorUniformColorLoc, 1, color);
    
    Vector3f LT, RT, LB, RB;
    LT = *array;
    RT = *(array+1);
    LB = *(array+2);
    RB = *(array+3);
    
    Vector3f center= Vector3f((LT.x + RT.x)/2.0f, (LT.y + RT.y)/2.0f, 0);
    drawRound(LT ,RT ,center);
    
    center = Vector3f((LB.x + RB.x)/2.0f, (LB.y + RB.y)/2.0f, 0);
    drawRound(RB ,LB ,center);
}

//LT 代表start
//RT 代表end
void MapImp::drawRound(glm::Vector3f from ,glm::Vector3f  to ,glm::Vector3f center){
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
    
    GLfloat vertices[3*(count+2)];
    for (int i = 0 ; i != count+2 ; ++i){
        Vector3f ver = vertexs[i];
        vertices[i*3+0] = ver.x;
        vertices[i*3+1] = ver.y;
        vertices[i*3+2] = ver.z;
    }
    
    GLushort indices[3*count];
    for (int i = 0 ; i != count ; ++i){
        indices[i*3+0] = 0;
        indices[i*3+1] = i+1;
        indices[i*3+2] = i+2;
    }
    
    drawArrays(vertices ,indices ,count*3);
}

void MapImp::drawArraysWithColor(glm::Vector3f*array ,GLfloat*color){
    Vector3f LTMat, RTMat, LBMat, RBMat;
    LTMat = *array;
    RTMat = *(array+1);
    LBMat = *(array+2);
    RBMat = *(array+3);
    
    glUniform4fv(colorUniformColorLoc, 1, color);
    
    GLfloat vertices[4 * (VERTEX_POS_SIZE)] = {
        RTMat.x,RTMat.y,0,
        RBMat.x,RBMat.y,0,
        LBMat.x,LBMat.y,0,
        LTMat.x,LTMat.y,0,
    };
    
    GLushort indices[6] = {0, 1, 3, 1, 2, 3};
    
    glVertexAttribPointer(colorAttributePosition, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (const void *)vertices);
    
    glDrawElements(GL_TRIANGLES, 6,
                   GL_UNSIGNED_SHORT, indices);
}

void MapImp::drawArrays(GLfloat*vertices ,GLushort*indices ,int count){
    glVertexAttribPointer(colorAttributePosition, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (const void *)vertices);
    
    glDrawElements(GL_TRIANGLES, count,
                   GL_UNSIGNED_SHORT, indices);
}


void MapImp::drawSegmentFrom(glm::Vector3f start ,glm::Vector3f to ,float width){
    Vector3f  vStart = screen2openGL2(start);
    Vector3f  vTo    = screen2openGL2(to);
    
    Vector3f * glStart = &vStart;
    Vector3f * glTo    = &vTo;
    
    float lineWidth = width / (mBackingWidth / 2.0f);
    
    //draw line
    colorShader->useProgram();
    
    GLfloat color[4] = {0.93,0.73,0.3,1.0f};
    
    //draw background
    drawSegment(glStart ,glTo ,lineWidth ,color);
    
    //draw fill
    float borderWidth = 1.0f / (mBackingWidth / 2.0f);
    GLfloat acolor[4] = {0.97, 0.87, 0.56,1.0f};
    drawSegment(glStart ,glTo ,lineWidth-borderWidth*2 ,acolor);
    
    //draw arrow
    glBindTexture(GL_TEXTURE_2D, arrowTexture);
    
    textureShader->useProgram();
    
    glUniform1i(uniformUseMixColor,1);
    
    drawArrowVertexs(vStart ,vTo ,5);
}

void MapImp::drawArrowVertexs(Vector3f start ,Vector3f to ,int arrowCount){
    Vector3f vecAB = to - start;
    
    Vector3f vecABNormal = glm::normalize(vecAB);
    
    float length = glm::length(vecAB);
    
    float width = arrowWidth / (mBackingWidth / 2.0f) / 2.0f;
    float height = arrowHeight / (mBackingWidth / 2.0f) / 2.0f;
    
    for (int i = 0 ; i < arrowCount ; ++i){
        Vector3f arrowCenter = start + (vecABNormal * ((i+1) * length / (arrowCount+1)));
        
        Vector3f * vertexts = LineDrawer::calcluateVertexsForCenter(arrowCenter ,vecAB ,height ,width);
        
        drawArraysWithTexture(vertexts ,1);
    }
}

/**
 绘制一个矩形，传入矩形的四个顶点的坐标
 */
void MapImp::drawArraysWithTexture(glm::Vector3f* array ,int scale){
    Vector3f LTMat, RTMat, LBMat, RBMat;
    LTMat = *array;
    RTMat = *(array+1);
    LBMat = *(array+2);
    RBMat = *(array+3);
    
    //    int scale = 4;
    GLfloat vertices[4 * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE)] = {
        
        RTMat.x,RTMat.y,0,
        1.0f * scale, 0,
        
        RBMat.x,RBMat.y,0,
        1.0f *scale, 1.0f * scale,
        
        LBMat.x,LBMat.y,0,
        0, 1.0f * scale,
        
        LTMat.x,LTMat.y,0,
        0, 0
    };
    
    GLushort indices[6] = {0, 1, 3, 1, 2, 3};
    
    glVertexAttribPointer(attribPosition, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (const void *)vertices);
    glVertexAttribPointer(attribTexCoord, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (const void *)(vertices+(VERTEX_POS_SIZE)));
    
    glDrawElements(GL_TRIANGLES, 6,
                   GL_UNSIGNED_SHORT, indices);
}


void MapImp::drawAALineFrom(glm::Vector3f start ,
                            glm::Vector3f to ,
                            float width){
    Vector3f  vStart = screen2openGL2(start);
    Vector3f  vTo    = screen2openGL2(to);
    
    const int count = 8;
    
    Vector3f mixVector[count] = {mix0, mix1, mix2, mix3, mix4, mix5, mix6, mix7};
    
    float lineWidth = width / (mBackingWidth);
    
    GLfloat ver[count*9];
    for (int i = 0 ; i != count; ++i){
        ver[i*9 + 0] = vStart.x;
        ver[i*9 + 1] = vStart.y;
        ver[i*9 + 2] = vStart.z;
        ver[i*9 + 3] = vTo.x;
        ver[i*9 + 4] = vTo.y;
        ver[i*9 + 5] = vTo.z;
        ver[i*9 + 6] = mixVector[i].x;
        ver[i*9 + 7] = mixVector[i].y;
        ver[i*9 + 8] = mixVector[i].z;
    }
    GLushort index[18] = {1,5,6, 1,6,2, 0, 4,5, 0,5,1, 2,6,7, 2,7,3};
    
    aalineShader->useProgram();
    
    GLint widthXY = aalineShader->getUniformLocation("lineWidthXY");
    float vec2WidthXY[2] = {lineWidth, lineWidth};
    glUniform2fv(widthXY, 1, vec2WidthXY);
    
    GLint mvp     = aalineShader->getUniformLocation("MVP");
    glm::Matrix4f matMVP = glm::Matrix4f(1.0f);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, matMVP.ptr());
    
    GLint aspect  = aalineShader->getUniformLocation("aspectAndRev");
    float vec2Aspect[2] = {1.0f, 1.0f};
    glUniform2fv(aspect, 1, vec2Aspect);
    
    GLint texUni = aalineShader->getUniformLocation("texUnit");
    glUniform1i(texUni, 0);
    
    GLint color  = aalineShader->getUniformLocation("color");
    float vec4Color[4] = {0, 0, 0, 1.0f};
    glUniform4fv(color, 1, vec4Color);
    
    GLint pos0 = aalineShader->getAttribLocation("position0");
    GLint pos1 = aalineShader->getAttribLocation("position1");
    GLint mix  = aalineShader->getAttribLocation("mixDirVer");
    glEnableVertexAttribArray(pos0);
    glEnableVertexAttribArray(pos1);
    glEnableVertexAttribArray(mix);
    
    glVertexAttribPointer(pos0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const void *)ver);
    glVertexAttribPointer(pos1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const void *)(ver+3));
    glVertexAttribPointer(mix , 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const void *)(ver+6));
    
    glDrawElements(GL_TRIANGLES, 18,
                   GL_UNSIGNED_SHORT, index);
}



void MapImp::loadBaseTexture(){
    GLubyte pixels[4*4] = {
        168, 0, 0,0,
        0,  168, 0,255,
        0,  0, 168,255,
        168, 168, 0,0
    };
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glGenTextures(1, &_baseTexture);
    
    glBindTexture(GL_TEXTURE_2D, _baseTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void MapImp::loadArrowTexture(const char * imagePath){
    //    NSString * imagePath = [[NSBundle mainBundle] pathForResource:@"color_arrow_texture" ofType:@"png"];
    
    GLubyte *image;
    
#if 1
    image = SOIL_load_image(imagePath, &arrowWidth, &arrowHeight, 0, SOIL_LOAD_RGBA);
#else
    CGContextRef textureContext;
    
    UIImage *uiImage = [UIImage imageNamed:imagePath];
    
    if (!uiImage){
        return;
    }
    
    size_t height = CGImageGetHeight(uiImage.CGImage);
    size_t width  = CGImageGetWidth(uiImage.CGImage);
    
    image = (GLubyte *) malloc(width * height * 4 );
    
    textureContext = CGBitmapContextCreate(image, width, height, 8, width * 4, CGImageGetColorSpace(uiImage.CGImage), kCGImageAlphaPremultipliedLast);
    CGContextSetBlendMode(textureContext, kCGBlendModeCopy);
    CGContextDrawImage(textureContext, CGRectMake(0.0, 0.0, (float)width, (float)height), uiImage.CGImage);
    
    arrowWidth  = width;
    arrowHeight = height;
    
    CGContextRelease(textureContext);
#endif
    
    glGenTextures(1, &arrowTexture);
    glBindTexture(GL_TEXTURE_2D, arrowTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, arrowWidth, arrowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SOIL_free_image_data(image);
}

void MapImp::loadLine3DTexture(float lineWidth){
    
    GLubyte * image = createTextureLine3D(lineWidth);
    
    //    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    //    NSString *docDir = [paths objectAtIndex:0];
    //
    //    NSString * saveImagePath = [docDir stringByAppendingString:@"/line3d.tga"];
    //
    //    NSLog(@"%@", saveImagePath);
    
    int width = nextPowerOfTwo(lineWidth);
    width = width < 8 ? 8 : width;
    
    
    //    int ret = SOIL_save_image([saveImagePath cString], SOIL_SAVE_TYPE_TGA, width, width, 4, image);
    
    glGenTextures(1, &aaLineTexture);
    glBindTexture(GL_TEXTURE_2D, aaLineTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, width, 0, GL_ALPHA, GL_UNSIGNED_BYTE, image);
    
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SOIL_free_image_data(image);
}

GLubyte * createTextureLine3D(int lineWidth){
    int width = nextPowerOfTwo(lineWidth);
    width = width < 8 ? 8 : width;
    GLubyte * data = (GLubyte*)malloc(width * width*sizeof(GLubyte));
    
    float radius = width;                           // 半圆外完全透明
    float pixelRadian = M_PI / radius;              // 每个像素对应的弧度
    for (int row = 0; row < width; ++row)
    {
        int rowbase = row * width * 1;
        for (int col = 0; col < width; ++col)
        {
            glm::Vector2f dir(col + 0.5f, row + 0.5f);
            float dis = glm::length(dir);
            
            unsigned char value = 0;
            if (dis < radius)
            {
                float radian = (radius - dis) * pixelRadian - M_PI_2;
                float sinR = sinf(radian);
                //float sign = sinR > 0.0f ? 1.0f : -1.0f;
                //float valuef = (sqrtf(fabsf(sinR)) * sign + 1.0f) * 0.5f * 255.0f;
                float valuef = (sinR + 1.0f) * 0.5f * 255.0f;
                value = valuef;
            }
            int base = rowbase + col * 1;
            *(data + base) = value;
        }
    }
    
    return data;
}


void MapImp::switch3D(){
    setMVPFor3D(textureShader);
    setMVPFor3D(colorShader);
    
    //     render:;
}

void MapImp::switch2D(){
    setMVPFor2D(textureShader);
    setMVPFor2D(colorShader);
    
    //    [self render:nil];
}

void MapImp::compileShaders(){
    textureShader  = new CShader(TextureVertex ,TextureFragment);
    
    attribPosition = textureShader->getAttribLocation("a_position");
    attribTexCoord = textureShader->getAttribLocation("a_texCoord");
    uniformTexture = textureShader->getUniformLocation("u_samplerTexture");
    uniformUseMixColor = textureShader->getUniformLocation("useMixColor");
    glEnableVertexAttribArray(attribPosition);
    glEnableVertexAttribArray(attribTexCoord);
    glUniform1i(uniformTexture, 0);
    
    setMVPFor2D(textureShader);
    
    colorShader = new CShader(ColorVertex,ColorFragment);
    colorAttributePosition = colorShader->getAttribLocation("position");
    colorUniformColorLoc = colorShader->getUniformLocation("color");
    
    setMVPFor2D(colorShader);
    
    aalineShader = new CShader(AALineVertex, AALineFragment);
}

void MapImp::setMVPFor3D(CShader *shader){
    shader->useProgram();
    
    GLuint colorUniformProjection = shader->getUniformLocation("projection");
    GLuint colorUniformModel = shader->getUniformLocation("model");
    GLuint colorUniformView = shader->getUniformLocation("view");
    
    glm::Matrix4<float> model;
    glm::Matrix4<float> view;
    glm::Matrix4<float> proj;
    
    //    model = glm::mat4(1.0f);
    //    view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation
    
    model = glm::rotate(model, - float(M_PI_4), glm::Vector3<float>(1.0f, 0.0f, 0.0f));
    view  = glm::translate(view, glm::Vector3<float>(0.0f, 0.0, -2.5f));
    proj  = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    
    glUniformMatrix4fv(colorUniformModel, 1, GL_FALSE, model.ptr());
    glUniformMatrix4fv(colorUniformView, 1, GL_FALSE, view.ptr());
    glUniformMatrix4fv(colorUniformProjection, 1, GL_FALSE, proj.ptr());
}


void MapImp::setMVPFor2D(CShader *shader){
    shader->useProgram();
    
    GLuint colorUniformProjection = shader->getUniformLocation("projection");
    GLuint colorUniformModel = shader->getUniformLocation("model");
    GLuint colorUniformView = shader->getUniformLocation("view");
    
    glm::Matrix4<float> model(1.0f);
    glm::Matrix4<float> view(1.0f);
    glm::Matrix4<float> proj(1.0f);
    
    glUniformMatrix4fv(colorUniformModel, 1, GL_FALSE, model.ptr());
    glUniformMatrix4fv(colorUniformView, 1, GL_FALSE, view.ptr());
    glUniformMatrix4fv(colorUniformProjection, 1, GL_FALSE, proj.ptr());
}


void MapImp::drawRoadLineString(glm::Vector3f *points
                                ,int pointCount
                                ,float lineWidth
                                ,float borderWidth){
    
    GLfloat borderColor[4] = {0.93,0.73,0.3,1.0f};
    
    drawLineString(points ,pointCount ,lineWidth ,borderColor);
    
    GLfloat fillColor[4] = {0.97, 0.87, 0.56,1.0f};
    
    drawLineString(points ,pointCount ,lineWidth-borderWidth*2.0f ,fillColor);
}

void MapImp::drawLineString(glm::Vector3f*points
                            ,int pointCount
                            ,float width
                            ,GLfloat* color){
    if (pointCount < 2){
        return;
    }
    
    colorShader->useProgram();
    
    float lineWidth = width / (mBackingWidth / 2.0f);
    
    Vector3f preLT, preRT, preLineDir;
    
    for (int i = 1 ;i < pointCount; ++i){
        
        Vector3f vStart  = screen2openGL2(points[i-1]);
        Vector3f  vTo    = screen2openGL2(points[i]);
        
        Vector3f curLineDir = glm::normalize((vTo - vStart));
        
        Vector3f * array = LineDrawer::calculateVertexsForRectangle(&vStart ,&vTo ,lineWidth);
        
        drawArraysWithColor(array ,color);
        
        Vector3f LT, RT, LB, RB;
        LT = *array;
        RT = *(array+1);
        LB = *(array+2);
        RB = *(array+3);
        
        //绘制起点末端的半圆
        if (i == 1){
            Vector3f center((LB.x + RB.x)/2.0f, (LB.y + RB.y)/2.0f, 0);
            drawRound(RB ,LB ,center);
        }
        
        //绘制终点末端的半圆
        if (i == pointCount - 1){
            Vector3f center((LT.x + RT.x)/2.0f, (LT.y + RT.y)/2.0f, 0);
            drawRound(LT ,RT ,center);
        }
        
        //绘制两个线段之间的转弯过度
        if (i >= 2){
            if (curLineDir.y > preLineDir.y || curLineDir.x < -preLineDir.x){
                //逆时针转，绘制右测转弯
                drawRound(RB ,preRT ,vStart);
            } else {
                //顺时针转，绘制左测转弯
                drawRound(preLT ,LB ,vStart);
            }
        }
        
        preLT = LT;
        preRT = RT;
        preLineDir = curLineDir;
    }
}












