#version 460 core
out vec4 FragColor;
uniform vec4 color;
void main()
{
    FragColor = vec4(color.x, color.y, color.z, color.w);
} 