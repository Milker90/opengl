#version 300 es

layout(location = 0) in vec3 Position;

out vec3 v_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void) {
    gl_Position = projection * view * model *  vec4(Position, 1.0f);
    v_normal = Position;
}
