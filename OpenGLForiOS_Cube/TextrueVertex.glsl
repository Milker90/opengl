uniform mat4 u_MVPMatrix;

attribute vec4 a_position;
attribute vec2 a_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec2 v_texCoord;

void main()
{
    gl_Position = projection * view * model * a_position;
    v_texCoord  = a_texCoord;
}
