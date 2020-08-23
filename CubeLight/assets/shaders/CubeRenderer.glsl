#type vertex
#version 450 core
layout(location = 0) in vec3 pos;

uniform mat4 vp;
void main()
{
    gl_Position = vp * vec4(pos, 1.0);
}

#type fragment
#version 450 core

out vec4 colour;
void main()
{
    colour = vec4(1.0);
}