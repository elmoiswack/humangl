#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;
uniform mat4 positivePivotMatrix;
uniform mat4 negativePivotMatrix;

uniform int walkingAnimation;

void main()
{
	if (walkingAnimation == 1)
	{
		gl_Position = perspective * view * positivePivotMatrix * model * negativePivotMatrix * vec4(aPos, 1);
	}
	else
	{
		gl_Position = perspective * view * model * vec4(aPos, 1);
	}
}