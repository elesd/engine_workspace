attribute vec3 position;
attribute vec4 color;

varying vec4 out_color;

void main()
{
    gl_Position = vec4(position.xyz, 1.0);
    out_color = color;
}
