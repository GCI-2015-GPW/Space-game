#version 330 core

layout (location = 0) in vec3 vertLocIn;

void main()
{
    gl_Position.xyz = vertLocIn;
    gl_Position.w = 1.f;
}
