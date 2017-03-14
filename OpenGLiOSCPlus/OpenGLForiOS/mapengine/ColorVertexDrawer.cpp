//
//  ColorVertexDrawer.cpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#include "ColorVertexDrawer.hpp"
#include "ShaderGLSL.h"

static const char * ColorFragment =
"precision highp float;"\
"uniform lowp vec4 color;"\
"void main()"\
"{"\
"   gl_FragColor = color;"\
"}";

static const char * ColorVertex =
"uniform mat4 u_MVPMatrix;"\
"attribute vec3 position;"\
"uniform mat4 MVP;"\
"void main()"\
"{"\
"    gl_Position = MVP * vec4(position,1.0);"\
"}";

ColorVertexDrawer::ColorVertexDrawer(){
    colorShader      = new CShader(ColorVertex,ColorFragment);
    positionLocation = colorShader->getAttribLocation("position");
    colorLocation    = colorShader->getUniformLocation("color");
    mvpLocation      = colorShader->getUniformLocation("MVP");
}

ColorVertexDrawer::~ColorVertexDrawer(){
    delete  colorShader;
}

void ColorVertexDrawer::drawRectangleWithColor(glm::Vector3f*array ,GLfloat*color){
    Vector3f LTMat, RTMat, LBMat, RBMat;
    LTMat = *array;
    RTMat = *(array+1);
    LBMat = *(array+2);
    RBMat = *(array+3);
    
    glUniform4fv(colorLocation, 1, color);
    
    GLfloat vertices[4 * 3] = {
        RTMat.x,RTMat.y,0,
        RBMat.x,RBMat.y,0,
        LBMat.x,LBMat.y,0,
        LTMat.x,LTMat.y,0,
    };
    
    GLushort indices[6] = {0, 1, 3, 1, 2, 3};
    
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (const void *)vertices);
    
    glDrawElements(GL_TRIANGLES, 6,
                   GL_UNSIGNED_SHORT, indices);
}

void ColorVertexDrawer::useProgram(){
    colorShader->useProgram();
}

void ColorVertexDrawer::setMVP(glm::Matrix4f mvp){
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.ptr());
}

void ColorVertexDrawer::setColor(GLfloat *color){
    glUniform4fv(colorLocation, 1, color);
}

void ColorVertexDrawer::drawArrays(GLfloat*vertices ,GLushort*indices ,int indexCount){
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (const void *)vertices);
    
    glDrawElements(GL_TRIANGLES, indexCount,
                   GL_UNSIGNED_SHORT, indices);
}
