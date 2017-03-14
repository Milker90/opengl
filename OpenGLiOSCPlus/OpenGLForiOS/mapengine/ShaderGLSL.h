//
//  ShaderGLSL.hpp
//  OpenGLForiOS
//
//  Created by lihuafeng on 2017/3/14.
//  Copyright © 2017年 lihuafeng. All rights reserved.
//

#ifndef ShaderGLSL_hpp
#define ShaderGLSL_hpp

#include <stdio.h>

static char *AALineFragment =
"varying mediump vec2 texCoord_f;"\
"uniform sampler2D texUnit;"\
"uniform lowp vec4 color;"\
"void main()"\
"{"\
"lowp vec4 fragColor = color;"\
"fragColor.a *= texture2D(texUnit, texCoord_f).a;"\
"gl_FragColor = fragColor;"\
"}";

static const char *AALineVertex =
"attribute vec4 position0;"\
"attribute vec4 position1;"\
"attribute vec3 mixDirVer;"\
"uniform mat4 MVP;"\
"uniform vec2 lineWidthXY;"\
"uniform vec2 aspectAndRev;"\
"varying mediump vec2 texCoord_f;"\
"void main()"\
"{"\
"   highp vec4 p0 = MVP * position0;"\
"   highp vec4 p1 = MVP * position1;"\
"   highp vec4 pos = mix(p0, p1, mixDirVer.x);"\

"   p0 /= p0.w;"\
"  p1 /= p1.w;"\

"   p0.y *= aspectAndRev.y;"\
"   p1.y *= aspectAndRev.y;"\

"   highp vec2 U = normalize((p1 - p0).xy);"\
"   highp vec2 V = vec2(-U.y, U.x);"\

"   highp vec2 offset = U * mixDirVer.y + V * mixDirVer.z;"\
"   offset *= lineWidthXY;"\
"   pos.xy += offset * pos.w;"\
"   pos.z -= 0.0002 * pos.w;"\

"   gl_Position = pos;"\

"   texCoord_f = mixDirVer.yz;"\
"}";

static const char * CubeFragment =
"#version 300 es"\
"precision lowp float;"\
"in vec3 v_normal;"\
"layout(location=0)out vec4 outColor;"\
"uniform samplerCube s_texture;"\
"void main(void) {"\
"    outColor = texture (s_texture, v_normal);"\
"}";

static const char * CubeVertex =
"#version 300 es"\
"layout(location = 0) in vec3 Position;"\
"out vec3 v_normal;"\
"uniform mat4 model;"\
"uniform mat4 view;"\
"uniform mat4 projection;"\
"void main(void) {"\
"   gl_Position = projection * view * model *  vec4(Position, 1.0f);"\
"   v_normal = Position;"\
"}";

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
"uniform mat4 model;"\
"uniform mat4 view;"\
"uniform mat4 projection;"\
"void main()"\
"{"\
"    gl_Position = projection * view * model * vec4(position,1.0);"\
"}";

static const char * TextureFragment =
"precision highp float;"\
"varying vec2 v_texCoord;"\
"uniform sampler2D u_samplerTexture;"\
"uniform bool useMixColor;"\
"void main()"\
"{"\
"    vec4 texColor = texture2D(u_samplerTexture, v_texCoord);"\
"    if (useMixColor){"\
"        gl_FragColor = texColor * vec4(1.0, 0, 0, 0.3);"\
"    } else {"\
"        gl_FragColor = texColor;"\
"   }"\
"}";

static const char * TextureVertex =
"uniform mat4 u_MVPMatrix;"\
"attribute vec3 a_position;"\
"attribute vec2 a_texCoord;"\
"uniform mat4 model;"\
"uniform mat4 view;"\
"uniform mat4 projection;"\
"varying vec2 v_texCoord;"\
"void main()"\
"{"\
"   gl_Position = projection * view * model * vec4(a_position, 1.0);"\
"   v_texCoord  = a_texCoord;"\
"}";


#endif /* ShaderGLSL_hpp */
