#version 300 es

layout(location = 0) in vec3 Position; // 1

out vec3 v_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void) { // 4
    gl_Position = projection * model * view * vec4(Position, 1.0f); // 6
//    gl_Position = vec4(Position, 1.0f); // 6
    v_normal = Position;
}
