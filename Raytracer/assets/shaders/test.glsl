#type vertex
#version 450 core

layout(location = 0) in vec3 pos;

void main()
{
	gl_Position = vec4(pos, 1.0);
}

#type fragment
#version 450 core

out vec4 colour;

void main()
{
	colour = vec4(1.0, 0.0, 0.0, 1.0);
}