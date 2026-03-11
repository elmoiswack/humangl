#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;

flat out int currentIndex;

void main()
{
	currentIndex = gl_VertexID;
	gl_Position = perspective * view * model * vec4(aPos, 1);
}