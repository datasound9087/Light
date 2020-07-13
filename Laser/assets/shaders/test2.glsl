#type vertex
#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

out vec2 tCoord;

void main()
{
	tCoord = texCoord;
	gl_Position = vec4(pos, 1.0);
}

#type fragment
#version 450 core

in vec2 tCoord;
out vec4 colour;

uniform sampler2D tex;

void main()
{
	
	colour = texture(tex, tCoord);
}