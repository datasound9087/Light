#type vertex
#version 450 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

out vec2 tCoord;
uniform mat4 vp;
void main()
{
    gl_Position = vp * vec4(pos, 1.0);
}

#type fragment
#version 450 core

in vec2 tCoord;
uniform sampler2D textureAtlas;
out vec4 colour;
void main()
{
    colour = texture(textureAtlas, tCoord);
}