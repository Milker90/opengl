//
//  CShader.h
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/3.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//
#ifndef _CSHADER_HEADER_H_
#define _CSHADER_HEADER_H_


#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

class CShader{
    
public:
    CShader(const char * vertex, const char * framgent);
    ~CShader();
    
    int getAttribLocation(const char* name);
    
    int getUniformLocation(const char* name);
    
    void useProgram();
    
private:
    GLuint compileShader(const char * shaderString ,int length, GLenum shaderType);
    
private:
    GLuint _programHandle;
};

#endif
