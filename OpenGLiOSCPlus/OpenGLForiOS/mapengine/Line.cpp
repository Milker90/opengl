//
//  Line.cpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#include "Line.hpp"
#include "ColorVertexDrawer.hpp"
#include "LineVertexCalculator.h"
#include "MapImp.h"

Line::Line(MapImp * map, ColorVertexDrawer * colorDrawer){
    mMap = map;
    mColorDrawer = colorDrawer;
}

Line::~Line(){
    
}

void Line::draw(glm::Vector3f*points,
                int pointCount,
                float lineWidth,
                GLfloat* color){
    if (pointCount < 2){
        return;
    }
    
    mColorDrawer->useProgram();
    
    Vector3f preLT, preRT, preLineDir;
    
    for (int i = 1 ;i < pointCount; ++i){
        
        Vector3f vStart  = mMap->screen2openGL2(points[i-1]);
        Vector3f  vTo    = mMap->screen2openGL2(points[i]);
        
        Vector3f curLineDir = glm::normalize((vTo - vStart));
        
        Vector3f * array = LineVertexCalculator::calculateVertexsForRectangle(&vStart ,&vTo ,lineWidth);
        
        mColorDrawer->drawRectangleWithColor(array ,color);
        
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

void Line::drawRound(glm::Vector3f from ,glm::Vector3f  to ,glm::Vector3f center){
    GLfloat * vertices;
    GLushort * indices;
    int indexCount;
    LineVertexCalculator::verticesForRound(from, to, center, vertices, indices, indexCount);
    
    mColorDrawer->drawArrays(vertices ,indices ,indexCount);
    
    delete[] vertices;
    delete[] indices;
}

void Line::drawSegment(glm::Vector3f*glStart ,
                       glm::Vector3f*glTo,
                       float lineWidth,
                       GLfloat* color){
    Vector3f * array = LineVertexCalculator::calculateVertexsForRectangle(glStart ,glTo ,lineWidth);
    mColorDrawer->drawRectangleWithColor(array ,color);
    
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
