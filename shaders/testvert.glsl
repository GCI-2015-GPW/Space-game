#version 300 es


precision highp float;

in vec3 vertLocIn;

void main()
{
    gl_Position.xyz = vertLocIn;
    gl_Position.w = 1.0;
}
