//
//  OpenGLView.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2016/12/23.
//  Copyright © 2016年 lihuafeng. All rights reserved.
//

#import "OpenGLView.h"
#include "SOIL.h"
#include "glm.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#import "LineDrawer.h"
//#include "learnopengl/camera.h"
#include "map.h"

#define VERTEX_POS_SIZE      3
#define VERTEX_COLOR_SIZE    2

#define VERTEX_STRIDE        (sizeof(GL_FLOAT) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE))

static const CC3Vector mix0 = {0.0f, -1.0f,  1.0f};
static const CC3Vector mix1 = {0.0f, 0.0f,   1.0f};
static const CC3Vector mix2 = {1.0f, 0.0f,   1.0f};
static const CC3Vector mix3 = {1.0f, 1.0f,   1.0f};
static const CC3Vector mix4 = {0.0f, -1.0f,  -1.0f};
static const CC3Vector mix5 = {0.0f, 0.0f,   -1.0f};
static const CC3Vector mix6 = {1.0f, 0.0f,   -1.0f};
static const CC3Vector mix7 = {1.0f, 1.0f,   -1.0f};

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
        
        
        [self setupRenderBuffer];
    
        
        [self compileShaders];
//        [self createMultiSampleBuffer];
        
//        glEnable(GL_DEPTH_TEST);
        glClearColor(0.95f, 0.95f, 0.91f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_MULTISAMPLE);
        
        
        
        [self render:nil];
    }
    
    return self;
}

-(void)switch3D{
    [self setMVPFor3D:textureShader];
    [self setMVPFor3D:colorShader];
    
    [self render:nil];
}

-(void)switch2D{
    [self setMVPFor2D:textureShader];
    [self setMVPFor2D:colorShader];
    
    [self render:nil];
}

-(void)compileShaders{
    textureShader = [[CShader alloc]init];
    [textureShader compileVertexShader:@"TextrueVertex" FragmentShader:@"TextureFragment"];
    
    attribPosition = [textureShader glGetAttribLocation:"a_position"];
    attribTexCoord = [textureShader glGetAttribLocation:"a_texCoord"];
    uniformTexture = [textureShader glGetUniformLocation:"u_samplerTexture"];
    uniformUseMixColor = [textureShader glGetUniformLocation:"useMixColor"];
    glEnableVertexAttribArray(attribPosition);
    glEnableVertexAttribArray(attribTexCoord);
    glUniform1i(uniformTexture, 0);
    
    [self setMVPFor2D:textureShader];
    
    colorShader = [[CShader alloc]init];
    [colorShader compileVertexShader:@"ColorVertex" FragmentShader:@"ColorFragment"];
    colorAttributePosition = [colorShader glGetAttribLocation:"position"];
    colorUniformColorLoc = [colorShader glGetUniformLocation:"color"];
    
    [self setMVPFor2D:colorShader];
    
    aalineShader = [[CShader alloc]init];
    [aalineShader compileVertexShader:@"AALineVertex" FragmentShader:@"AALineFragment"];
}

-(void)setMVPFor3D:(CShader *)shader{
    [shader useProgram];
    
    GLuint colorUniformProjection = [shader glGetUniformLocation:"projection"];
    GLuint colorUniformModel = [shader glGetUniformLocation:"model"];
    GLuint colorUniformView = [shader glGetUniformLocation:"view"];
    
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


-(void)setMVPFor2D:(CShader *)shader{
    [shader useProgram];
    
    GLuint colorUniformProjection = [shader glGetUniformLocation:"projection"];
    GLuint colorUniformModel = [shader glGetUniformLocation:"model"];
    GLuint colorUniformView = [shader glGetUniformLocation:"view"];
    
    glm::Matrix4<float> model(1.0f);
    glm::Matrix4<float> view(1.0f);
    glm::Matrix4<float> proj(1.0f);
    
    glUniformMatrix4fv(colorUniformModel, 1, GL_FALSE, model.ptr());
    glUniformMatrix4fv(colorUniformView, 1, GL_FALSE, view.ptr());
    glUniformMatrix4fv(colorUniformProjection, 1, GL_FALSE, proj.ptr());
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

-(void)loadLine3DTexture:(float)lineWidth{

    GLubyte * image = [self createTextureLine3D:lineWidth];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *docDir = [paths objectAtIndex:0];
    
    NSString * saveImagePath = [docDir stringByAppendingString:@"/line3d.tga"];
    
    NSLog(@"%@", saveImagePath);
    
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
    
    free(image);
}

-(GLubyte *) createTextureLine3D:(int)lineWidth{
    int width = nextPowerOfTwo(lineWidth);
    width = width < 8 ? 8 : width;
    GLubyte * data = (GLubyte*)malloc(width * width*sizeof(GLubyte));
    
    int a = sizeof(GLubyte);
    int b = sizeof(unsigned char);
    
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
//            *(data + base*4+0) = 0;
//            *(data + base*4+1) = 0;
//            *(data + base*4+2) = 0;
            *(data + base) = value;
        }
    }
    
    return data;
}

-(void)drawAALineFrom:(CC3Vector) start To:(CC3Vector)to width:(float)width{
    CC3Vector  vStart = [self screen2openGL:&start];
    CC3Vector  vTo    = [self screen2openGL:&to];
    
    const int count = 8;
    
    CC3Vector mixVector[count] = {mix0, mix1, mix2, mix3, mix4, mix5, mix6, mix7};
    
    float lineWidth = width / (self.frame.size.width);
    
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
    
    [aalineShader useProgram];
    
    GLint widthXY = [aalineShader glGetUniformLocation:"lineWidthXY"];
    float vec2WidthXY[2] = {lineWidth, lineWidth};
    glUniform2fv(widthXY, 1, vec2WidthXY);
    
    GLint mvp     = [aalineShader glGetUniformLocation:"MVP"];
    glm::Matrix4f matMVP = glm::Matrix4f(1.0f);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, matMVP.ptr());
    
    GLint aspect  = [aalineShader glGetUniformLocation:"aspectAndRev"];
    float vec2Aspect[2] = {1.0f, 1.0f};
    glUniform2fv(aspect, 1, vec2Aspect);
    
    GLint texUni = [aalineShader glGetUniformLocation:"texUnit"];
    glUniform1i(texUni, 0);
    
    GLint color  = [aalineShader glGetUniformLocation:"color"];
    float vec4Color[4] = {0, 0, 0, 1.0f};
    glUniform4fv(color, 1, vec4Color);
    
    GLint pos0 = [aalineShader glGetAttribLocation:"position0"];
    GLint pos1 = [aalineShader glGetAttribLocation:"position1"];
    GLint mix  = [aalineShader glGetAttribLocation:"mixDirVer"];
    glEnableVertexAttribArray(pos0);
    glEnableVertexAttribArray(pos1);
    glEnableVertexAttribArray(mix);
    
    glVertexAttribPointer(pos0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const void *)ver);
    glVertexAttribPointer(pos1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const void *)(ver+3));
    glVertexAttribPointer(mix , 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const void *)(ver+6));
    
    glDrawElements(GL_TRIANGLES, 18,
                   GL_UNSIGNED_SHORT, index);
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


-(void)drawSegment:(CC3Vector*)glStart
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
    [self loadBaseTexture];
    [self loadArrowTexture];
    
//    glBindFramebuffer(GL_FRAMEBUFFER, sampleFramebuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, sampleColorRenderbuffer);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, self.frame.size.width, self.frame.size.width);
    
    //hahaha
    
    CC3Vector start, to;
    start.x = 100;
    start.y = 70;
    start.z = 0;
    
    to.x = 300.0f;
    to.y = 90;
    to.z = 0;
    
    float width = 20.0f;
    
//    [self drawSegmentFrom:start To:to width:width];
    
    
    [colorShader useProgram];
    
    GLfloat color[4] = {1,0,0,0.5f};
    {
        CC3Vector s = [self screen2openGL2:CC3VectorMake(100, 150, 0)];
        CC3Vector e = [self screen2openGL2:CC3VectorMake(300,170, 0)];
        float lineWidth = 40.0f / (self.frame.size.width / 2.0f);
        [self drawSegment:&s To:&e width:lineWidth color:color];
    }
    
    [self loadLine3DTexture:40.0f];
    glBindTexture(GL_TEXTURE_2D, aaLineTexture);
    [self drawAALineFrom:CC3VectorMake(100, 150, 0) To:CC3VectorMake(300, 170, 0) width:40.0f];
    
    [self drawAALineFrom:CC3VectorMake(100, 70, 0) To:CC3VectorMake(300, 90, 0) width:40.0f];
    
    [self drawSegmentFrom:CC3VectorMake(20, 30, 0) To:CC3VectorMake(350, 30, 0) width:width];
    
    [self drawSegmentFrom:CC3VectorMake(30, 70, 0) To:CC3VectorMake(30, 300, 0) width:width];

    CC3Vector lines[9];
    lines[0] = CC3VectorMake(100, 150, 0);
    lines[1] = CC3VectorMake(100, 250, 0);
    lines[2] = CC3VectorMake(200, 250, 0);
    lines[3] = CC3VectorMake(200, 350, 0);
    lines[4] = CC3VectorMake(250, 300, 0);
    lines[5] = CC3VectorMake(300, 350, 0);
    lines[6] = CC3VectorMake(300, 200, 0);
    lines[7] = CC3VectorMake(350, 150, 0);
    lines[8] = CC3VectorMake(150, 150, 0);
    
//    [self drawRoadLineString:lines pointCount:9 lineWidth:width borderWidth:1.0f];
    
    
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

-(CC3Vector)screen2openGL2:(CC3Vector)coor{
    CC3Vector  ret ;
    
    float screenWidth  = self.frame.size.width;
    float screenHeight = self.frame.size.height;
    
    ret.x = (coor.x - screenWidth/2.0f) / (screenWidth / 2.0f);
    ret.y = (coor.y - screenWidth/2.0f) / (screenWidth / 2.0f);
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
