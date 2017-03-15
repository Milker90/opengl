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
    
    GLuint vertexShader   = compileShader(vertex, (int)strlen(vertex), GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(framgent, (int)strlen(framgent), GL_FRAGMENT_SHADER);
    
    _programHandle = glCreateProgram();
    glAttachShader(_programHandle, vertexShader);
    glAttachShader(_programHandle, fragmentShader);
    glLinkProgram(_programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(_programHandle, sizeof(messages), 0, &messages[0]);
        exit(1);
    }
    
    glUseProgram(_programHandle);
}

CShader::~CShader(){
    glDeleteProgram(_programHandle);
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
    GLuint shaderHandle = glCreateShader(shaderType);
    
    glShaderSource(shaderHandle, 1, &shaderString, &length);
    
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
//        printf(messages);
        exit(1);
    }
    
    return shaderHandle;
}
