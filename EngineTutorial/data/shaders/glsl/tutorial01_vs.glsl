
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 outColor;

void main(){

    gl_Position.xyz = position;
    gl_Position.w = 1.0;
    outColor = color;

}
