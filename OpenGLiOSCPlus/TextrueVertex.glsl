uniform mat4 u_MVPMatrix;

attribute vec3 a_position;
attribute vec2 a_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec2 v_texCoord;

void main()
{
    gl_Position = projection * view * model * vec4(a_position, 1.0);
    v_texCoord  = a_texCoord;
}
