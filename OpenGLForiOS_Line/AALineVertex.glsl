attribute vec4 position0;
attribute vec4 position1;
attribute vec3 mixDirVer;
uniform mat4 MVP;
uniform vec2 lineWidthXY;
uniform vec2 aspectAndRev;
varying mediump vec2 texCoord_f;

void main()
{
    highp vec4 p0 = MVP * position0;
    highp vec4 p1 = MVP * position1;
    highp vec4 pos = mix(p0, p1, mixDirVer.x);
    
    p0 /= p0.w;
    p1 /= p1.w;
    
    p0.y *= aspectAndRev.y;
    p1.y *= aspectAndRev.y;
    
    highp vec2 U = normalize((p1 - p0).xy);
    highp vec2 V = vec2(-U.y, U.x);
    
    highp vec2 offset = U * mixDirVer.y + V * mixDirVer.z;
    offset *= lineWidthXY;
    pos.xy += offset * pos.w;
    pos.z -= 0.0002 * pos.w;
    
    gl_Position = pos;
    
    texCoord_f = mixDirVer.yz;
}
