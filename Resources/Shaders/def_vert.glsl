#version 460 core
layout(location = 0) in vec3 aPos;

uniform mat4 M; // Model matrix
uniform mat4 P; // Projection matrix
uniform mat4 V; // View matrix

void main()
{
    gl_Position = P * V* M * vec4(aPos, 1.0);
}