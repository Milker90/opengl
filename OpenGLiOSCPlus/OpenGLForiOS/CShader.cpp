//
//  CShader.m
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/3.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#include "CShader.h"
#include "stdlib.h"
#include "string.h"


CShader::CShader(const char * vertex, const char * framgent) {
    
    // 1
    GLuint vertexShader   = compileShader(vertex, strlen(vertex), GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(framgent, strlen(framgent), GL_FRAGMENT_SHADER);
    
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
//        NSString *messageString = [NSString stringWithUTF8String:messages];
//        NSLog(@"%@", messageString);
        exit(1);
    }
    
    // 4
    glUseProgram(_programHandle);
}

void CShader::useProgram(){
    glUseProgram(_programHandle);
}

int CShader::getAttribLocation(const char* name){
    return glGetAttribLocation(_programHandle, name);
}

int CShader::getUniformLocation(const GLchar* name){
    return glGetUniformLocation(_programHandle, name);
}

GLuint CShader::compileShader(const char * shaderString , int length, GLenum shaderType) {
    // 2
    GLuint shaderHandle = glCreateShader(shaderType);
    
    // 3
//    const char* shaderStringUTF8 = shaderString.c_str();
//    int shaderStringLength = shaderString.length();
    glShaderSource(shaderHandle, 1, &shaderString, &length);
    
    // 4
    glCompileShader(shaderHandle);
    
    // 5
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
//        NSString *messageString = [NSString stringWithUTF8String:messages];
//        NSLog("%@", messageString);
//        printf(messages);
        exit(1);
    }
    
    return shaderHandle;
}
