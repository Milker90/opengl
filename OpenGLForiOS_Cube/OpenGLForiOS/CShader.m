//
//  CShader.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/3.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import "CShader.h"
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

@interface CShader(){
    GLuint _programHandle;
}

@end

@implementation CShader

- (void)compileVertexShader:(NSString*)vertexShaderName
             FragmentShader:(NSString*)fragmentShaderName {
    
    // 1
    GLuint vertexShader = [self compileShader:vertexShaderName
                                     withType:GL_VERTEX_SHADER];
    GLuint fragmentShader = [self compileShader:fragmentShaderName
                                       withType:GL_FRAGMENT_SHADER];
    
    // 2
    _programHandle = glCreateProgram();
    glAttachShader(_programHandle, vertexShader);
    glAttachShader(_programHandle, fragmentShader);
    glLinkProgram(_programHandle);
    
    // 3
    GLint linkSuccess;
    glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(_programHandle, sizeof(messages), 0, &messages[0]);
        NSString *messageString = [NSString stringWithUTF8String:messages];
        NSLog(@"%@", messageString);
        exit(1);
    }
    
    // 4
    glUseProgram(_programHandle);
}

-(void)useProgram{
    glUseProgram(_programHandle);
}

-(int) glGetAttribLocation: (const GLchar*) name{
    return glGetAttribLocation(_programHandle, name);
}

-(int) glGetUniformLocation: (const GLchar*) name{
    return glGetUniformLocation(_programHandle, name);
}

- (GLuint)compileShader:(NSString*)shaderName withType:(GLenum)shaderType {
    
    // 1
    NSString* shaderPath = [[NSBundle mainBundle] pathForResource:shaderName
                                                           ofType:@"glsl"];
    NSError* error;
    NSString* shaderString = [NSString stringWithContentsOfFile:shaderPath
                                                       encoding:NSUTF8StringEncoding error:&error];
    if (!shaderString) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    
    // 2
    GLuint shaderHandle = glCreateShader(shaderType);
    
    // 3
    const char* shaderStringUTF8 = [shaderString UTF8String];
    int shaderStringLength = [shaderString length];
    glShaderSource(shaderHandle, 1, &shaderStringUTF8, &shaderStringLength);
    
    // 4
    glCompileShader(shaderHandle);
    
    // 5
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        NSString *messageString = [NSString stringWithUTF8String:messages];
        NSLog(@"%@", messageString);
        exit(1);
    }
    
    return shaderHandle;
}

@end
