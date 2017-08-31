
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 ProjectionViewWorldMatrix;
uniform vec4 instanceColor;

out vec4 outColor;

void main()
{
    gl_Position = ProjectionViewWorldMatrix * position;
    outColor = color + instanceColor;

}
