//
//  OpenGLView.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2016/12/23.
//  Copyright © 2016年 lihuafeng. All rights reserved.
//

#import "OpenGLView.h"
#include "SOIL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#import "LineDrawer.h"
#include "learnopengl/camera.h"

#define VERTEX_POS_SIZE      3
#define VERTEX_COLOR_SIZE    2

#define VERTEX_STRIDE        (sizeof(GL_FLOAT) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE))

typedef struct {
    float Position[3];
    float Color[4];
} Vertex;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

float currentRotate;

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLfloat cubeVertices[] = {
    // Positions          // Normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



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
        
        [self destroyRenderAndFrameBuffer];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        
        [self createMultiSampleBuffer];
        
        [self compileShaders];
        
        [self setupCubeVBOs];
        
        [self setupDisplayLink];
        
        glViewport(0, 0, self.frame.size.width, self.frame.size.width);
        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_MULTISAMPLE);
        
        [self render:nil];
    }
    
    return self;
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

-(void)switch3D{
    [self setMVPFor3D:textureShader];
    [self setMVPFor3D:colorShader];
    [self setMVPFor3D:cubeShader];
    
    [self render:nil];
}

-(void)switch2D{
    [self setMVPFor2D:textureShader];
    [self setMVPFor2D:colorShader];
    [self setMVPFor2D:cubeShader];
    
    [self render:nil];
}

-(void)move:(int)offsetX y:(int)offsetY{
//    camera.ProcessMouseMovement(offsetX, offsetY);
}

-(void)compileShaders{
//    textureShader = [[CShader alloc]init];
//    [textureShader compileVertexShader:@"TextrueVertex" FragmentShader:@"TextureFragment"];
//    
//    attribPosition = [textureShader glGetAttribLocation:"a_position"];
//    attribTexCoord = [textureShader glGetAttribLocation:"a_texCoord"];
//    uniformTexture = [textureShader glGetUniformLocation:"u_samplerTexture"];
//    uniformUseMixColor = [textureShader glGetUniformLocation:"useMixColor"];
//    glEnableVertexAttribArray(attribPosition);
//    glEnableVertexAttribArray(attribTexCoord);
//    glUniform1i(uniformTexture, 0);
//    
//    [self setMVPFor2D:textureShader];
//    
//    colorShader = [[CShader alloc]init];
//    [colorShader compileVertexShader:@"ColorVertex" FragmentShader:@"ColorFragment"];
//    colorAttributePosition = [colorShader glGetAttribLocation:"position"];
//    colorUniformColorLoc = [colorShader glGetUniformLocation:"color"];
//    
//    [self setMVPFor2D:colorShader];
    
    cubeShader = [[CShader alloc]init];
    [cubeShader compileVertexShader:@"CubeVertex" FragmentShader:@"CubeFragment"];
    
    GLuint _samplerCube = [cubeShader glGetUniformLocation:"s_texture"];
    glUniform1f(_samplerCube, 0);
    
    [self setMVPFor3D:cubeShader];
}

-(void)setMVPFor3D:(CShader *)shader{
    [shader useProgram];
    
    GLuint colorUniformProjection = [shader glGetUniformLocation:"projection"];
    GLuint colorUniformModel = [shader glGetUniformLocation:"model"];
    GLuint colorUniformView = [shader glGetUniformLocation:"view"];
    
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    
    model = glm::rotate(model, currentRotate, glm::vec3(0.5f, 1.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    proj  = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    
    glUniformMatrix4fv(colorUniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(colorUniformView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(colorUniformProjection, 1, GL_FALSE, glm::value_ptr(proj));
}


-(void)setMVPFor2D:(CShader *)shader{
    [shader useProgram];
    
    GLuint colorUniformProjection = [shader glGetUniformLocation:"projection"];
    GLuint colorUniformModel = [shader glGetUniformLocation:"model"];
    GLuint colorUniformView = [shader glGetUniformLocation:"view"];
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    
    glUniformMatrix4fv(colorUniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(colorUniformView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(colorUniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
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
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

-(void)setupFrameBuffer{
    glGenFramebuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

-(void)destroyRenderAndFrameBuffer{
    glDeleteFramebuffers(1, &_frameBuffer);
    _frameBuffer = 0;
    glDeleteRenderbuffers(1, &_colorRenderBuffer);
    _colorRenderBuffer = 0;
}

-(void)createMultiSampleBuffer{
    mBackingWidth = self.frame.size.width;
    mBackingHeight = self.frame.size.height;
    
    glGenFramebuffers(1, &sampleFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, sampleFramebuffer);
    
    glGenRenderbuffers(1, &sampleColorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, sampleColorRenderbuffer);
    
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, mBackingWidth, mBackingHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, sampleColorRenderbuffer);
    
    glGenRenderbuffers(1, &sampleDepthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, sampleDepthRenderbuffer);
    
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT16, mBackingWidth, mBackingHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, sampleDepthRenderbuffer);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
}

-(void)loadBaseTexture{
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

-(void)loadArrowTexture{
    NSString * imagePath = [[NSBundle mainBundle] pathForResource:@"color_arrow_texture" ofType:@"png"];
    
    GLubyte *image;
    
#if 0
    image = SOIL_load_image([imagePath cString], &arrowWidth, &arrowHeight, 0, SOIL_LOAD_RGBA);
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
    
    free(image);
}

/*
 */
-(void)drawSegmentFrom:(CC3Vector) start To:(CC3Vector)to width:(float)width{
    CC3Vector  vStart = [self screen2openGL:&start];
    CC3Vector  vTo    = [self screen2openGL:&to];
    
    CC3Vector * glStart = &vStart;
    CC3Vector * glTo    = &vTo;
    
    float lineWidth = width / (self.frame.size.width / 2.0f);
    
    //draw line
    [colorShader useProgram];
    
    GLfloat color[4] = {0.93,0.73,0.3,1.0f};
    
    //draw background
    [self drawSegment:glStart To:glTo width:lineWidth color:color];
    
    //draw fill
    float borderWidth = 1.0f / (self.frame.size.width / 2.0f);
    GLfloat acolor[4] = {0.97, 0.87, 0.56,1.0f};
    [self drawSegment:glStart To:glTo width:lineWidth-borderWidth*2 color:acolor];
    
    //draw arrow
    glBindTexture(GL_TEXTURE_2D, arrowTexture);
    
    [textureShader useProgram];
    
    glUniform1i(uniformUseMixColor,1);
    
    [self drawArrowVertexs:vStart to:vTo arrowCount:5];
}

-(void)drawRoadLineString:(CC3Vector*)points
           pointCount:(int)pointCount
                lineWidth:(float)lineWidth
              borderWidth:(float)borderWidth{
    
    GLfloat borderColor[4] = {0.93,0.73,0.3,1.0f};

    [self drawLineString:points pointCount:pointCount width:lineWidth color:borderColor];
    
    GLfloat fillColor[4] = {0.97, 0.87, 0.56,1.0f};
    
    [self drawLineString:points pointCount:pointCount width:lineWidth-borderWidth*2.0f color:fillColor];
}

-(void)drawLineString:(CC3Vector*)points
           pointCount:(int)pointCount
             width:(float)width
             color:(GLfloat*)color{
    if (pointCount < 2){
        return;
    }
    
    [colorShader useProgram];
    
    float lineWidth = width / (self.frame.size.width / 2.0f);
    
    CC3Vector preLT, preRT, preLineDir;
    
    for (int i = 1 ;i < pointCount; ++i){
        
        CC3Vector vStart  = [self screen2openGL:&points[i-1]];
        CC3Vector  vTo    = [self screen2openGL:&points[i]];
        
        CC3Vector curLineDir = CC3VectorNormalize(CC3VectorDifference(vTo, vStart));
        
        CC3Vector * array = [LineDrawer calculateVertexsForRectangleFrom:&vStart To:&vTo width:lineWidth];
        
        [self drawArraysWithColor:array color:color];
        
        CC3Vector LT, RT, LB, RB;
        LT = *array;
        RT = *(array+1);
        LB = *(array+2);
        RB = *(array+3);
        
        //绘制起点末端的半圆
        if (i == 1){
            CC3Vector center = CC3VectorMake((LB.x + RB.x)/2.0f, (LB.y + RB.y)/2.0f, 0);
            [self drawRound:RB to:LB center:center];
        }
        
        //绘制终点末端的半圆
        if (i == pointCount - 1){
            CC3Vector center= CC3VectorMake((LT.x + RT.x)/2.0f, (LT.y + RT.y)/2.0f, 0);
            [self drawRound:LT to:RT center:center];
        }
        
        //绘制两个线段之间的转弯过度
        if (i >= 2){
            if (curLineDir.y > preLineDir.y || curLineDir.x < -preLineDir.x){
                //逆时针转，绘制右测转弯
                [self drawRound:RB to:preRT center:vStart];
            } else {
                //顺时针转，绘制左测转弯
                [self drawRound:preLT to:LB center:vStart];
            }
        }
        
        preLT = LT;
        preRT = RT;
        preLineDir = curLineDir;
    }
}


-(void)drawSegment:(CC3Vector*) glStart
             To:(CC3Vector*)glTo
          width:(float)lineWidth
          color:(GLfloat*)color{
    
    CC3Vector * array = [LineDrawer calculateVertexsForRectangleFrom:glStart To:glTo width:lineWidth];
    [self drawArraysWithColor:array color:color];
    glUniform4fv(colorUniformColorLoc, 1, color);
    
    CC3Vector LT, RT, LB, RB;
    LT = *array;
    RT = *(array+1);
    LB = *(array+2);
    RB = *(array+3);
    
    CC3Vector center= CC3VectorMake((LT.x + RT.x)/2.0f, (LT.y + RT.y)/2.0f, 0);
    [self drawRound:LT to:RT center:center];
    
    center = CC3VectorMake((LB.x + RB.x)/2.0f, (LB.y + RB.y)/2.0f, 0);
    [self drawRound:RB to:LB center:center];
}

//LT 代表start
//RT 代表end
-(void)drawRound:(CC3Vector)from to:(CC3Vector)to center:(CC3Vector)center{
//    GLfloat color[4] = {1.0, 0, 0,1.0f};
//    glUniform4fv(colorUniformColorLoc, 1, color);
    
    CC3Vector start = CC3VectorDifference(from, center);
    CC3Vector end   = CC3VectorDifference(to, center);
    
    CC3Vector startNor = CC3VectorNormalize(start);
    CC3Vector endNor   = CC3VectorNormalize(end);
    
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
    CC3Vector vertexs[count+2];
    vertexs[0] = center;
    vertexs[1] = from;
    
    for (int i = 1 ;i < count ; ++i){
        float a  = -delta/count * i;//注意方向
        float sa = sinf(a);
        float ca = cosf(a);
        
        float x = start.x * ca - start.y * sa;
        float y = start.x * sa + start.y * ca;
        
        CC3Vector newVec = CC3VectorMake(x, y, 0.0f);
        
        CC3Vector vertex = CC3VectorAdd(center, newVec);
        
        vertexs[i+1] = vertex;
    }
    
    vertexs[count+1] = to;
    
    GLfloat vertices[3*(count+2)];
    for (int i = 0 ; i != count+2 ; ++i){
        CC3Vector ver = vertexs[i];
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
    
    [self drawArrays:vertices index:indices count:count*3];
}

-(void)drawArrowVertexs:(CC3Vector)start to:(CC3Vector)to arrowCount:(int)arrowCount{
    CC3Vector vecAB = CC3VectorDifference(to, start);
    
    CC3Vector vecABNormal = CC3VectorNormalize(vecAB);
    
    float length = CC3VectorLength(vecAB);
    
    float width = arrowWidth / (self.frame.size.width / 2.0f) / 2.0f;
    float height = arrowHeight / (self.frame.size.width / 2.0f) / 2.0f;
    
    for (int i = 0 ; i < arrowCount ; ++i){
        CC3Vector arrowCenter = CC3VectorAdd (start , CC3VectorScaleUniform(vecABNormal,(i+1) * length / (arrowCount+1)));
        
        CC3Vector * vertexts = [LineDrawer calcluateVertexsForCenter:arrowCenter direction:vecAB height:height width:width];
        
        [self drawArraysWithTexture:vertexts scale:1];
    }
}

/**
 绘制一个矩形，传入矩形的四个顶点的坐标
 */
-(void)drawArraysWithTexture:(CC3Vector*)array scale:(int)scale{
    CC3Vector LTMat, RTMat, LBMat, RBMat;
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

-(void)drawArraysWithColor:(CC3Vector*)array color:(GLfloat*)color{
    CC3Vector LTMat, RTMat, LBMat, RBMat;
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

-(void)drawArrays:(GLfloat*)vertices index:(GLushort*)indices count:(int)count{
    glVertexAttribPointer(colorAttributePosition, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (const void *)vertices);
    
    glDrawElements(GL_TRIANGLES, count,
                   GL_UNSIGNED_SHORT, indices);
}

- (void)render:(CADisplayLink*)displayLink{
//    currentRotate = displayLink.duration * 50;
//    currentRotate = sin(CACurrentMediaTime()) * 50;
    currentRotate += displayLink.duration * M_PI_2;
    
    glBindFramebuffer(GL_FRAMEBUFFER, sampleFramebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, sampleColorRenderbuffer);
    
    
    glClearColor(0.95f, 0.95f, 0.91f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // Cubes

    [self setMVPFor3D:cubeShader];
    
//    [cubeShader useProgram];
//
//    GLuint colorUniformModel = [cubeShader glGetUniformLocation:"model"];
    
    glBindVertexArrayOES(cubeVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
//    for (int i = 0 ; i < 10; ++i){
//        glm::mat4 model;
//        model = glm::translate(model, cubePositions[i]);
//        GLfloat angle = 20.0f * i;
//        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
//        glUniformMatrix4fv(colorUniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
//    }
    
    glBindVertexArrayOES(0);
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, _frameBuffer);
    glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, sampleFramebuffer);
    

    // opengl 2.0
//    glResolveMultisampleFramebufferAPPLE();
//    const GLenum discards[]  = {GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT};
//    glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE,2,discards);
    
    // opengl 3.0
    glInvalidateFramebuffer(GL_READ_FRAMEBUFFER, 1, (GLenum[]){GL_DEPTH_ATTACHMENT});
    
    // Copy the read fbo(multisampled framebuffer) to the draw fbo(single-sampled framebuffer)
    glBlitFramebuffer(0, 0, mBackingWidth, mBackingHeight, 0, 0, mBackingWidth, mBackingHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    
    glInvalidateFramebuffer(GL_READ_FRAMEBUFFER, 1, (GLenum[]){GL_COLOR_ATTACHMENT0});
    
    //end
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    
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

- (void)setupCubeVBOs {
    [cubeShader useProgram];
    int pos = [cubeShader glGetAttribLocation:"Position"];
//    int nor = [cubeShader glGetAttribLocation:"a_normal"];
    
    // Setup cube VAO
//        GLuint cubeVAO, cubeVBO;
    glGenVertexArraysOES(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArrayOES(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(nor);
//    glVertexAttribPointer(nor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArrayOES(0);
    
    // Cubemap (Skybox)
    NSMutableArray * faces = [[NSMutableArray alloc]init];
    
    [faces addObject:[[NSBundle mainBundle] pathForResource:@"right" ofType:@"jpeg"]];
    [faces addObject:[[NSBundle mainBundle] pathForResource:@"left" ofType:@"jpeg"]];
    [faces addObject:[[NSBundle mainBundle] pathForResource:@"top" ofType:@"jpeg"]];
    [faces addObject:[[NSBundle mainBundle] pathForResource:@"bottom" ofType:@"jpeg"]];
    [faces addObject:[[NSBundle mainBundle] pathForResource:@"back" ofType:@"jpeg"]];
    [faces addObject:[[NSBundle mainBundle] pathForResource:@"front" ofType:@"jpeg"]];
    
    skyboxTexture = [self loadCubemap:faces];
}

-(GLuint) loadCubemap:(NSArray* )faces
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    
    int width,height;
    unsigned char* image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < [faces count]; i++)
    {
        NSString * path = [faces objectAtIndex:i];
        image = SOIL_load_image([path cString], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}


@end
