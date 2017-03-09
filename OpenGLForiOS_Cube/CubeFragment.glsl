#version 300 es

precision lowp float;

in vec3 v_normal;

layout(location=0)out vec4 outColor;

uniform samplerCube s_texture;

void main(void) {
    outColor = texture (s_texture, v_normal);
}
