//
//  CShader.h
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/3.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CShader : NSObject


- (void)compileVertexShader:(NSString*)vertexShaderName
             FragmentShader:(NSString*)fragmentShaderName;

-(int) glGetAttribLocation: (const GLchar*) name;

-(int) glGetUniformLocation: (const GLchar*) name;

-(void)useProgram;

@end
