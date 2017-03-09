#version 300 es


layout(location = 0) in vec3 Position; // 1
layout(location = 1) in vec3 a_normal; // 2

out vec3 v_normal;

uniform mat4 Projection;
uniform mat4 Modelview;
uniform mat4 model;

void main(void) { // 4
//    v_normal = a_normal;
    gl_Position = Projection * Modelview * model * vec4(Position,1.0f); // 6
    v_normal = Position;
}
