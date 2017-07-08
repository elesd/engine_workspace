layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 out_color;

void main()
{
    gl_Position.xyz = vec4(position.xyz, 1.0);
    out_color = color;
}
