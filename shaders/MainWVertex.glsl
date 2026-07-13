#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;
uniform mat4 positivePivotMatrix;
uniform mat4 negativePivotMatrix;

uniform int animation;
uniform float jumpHeight;

void main()
{
	int walkingAnimation = 1;
	int jumpAnimation = 2;
	int runAnimation = 3;
	int testAnimation = 4;

	if ((animation == walkingAnimation) || (animation == runAnimation))
	{
		gl_Position = perspective * view * positivePivotMatrix * model * negativePivotMatrix * vec4(aPos, 1);
	}
	else if (animation == jumpAnimation)
	{
		vec3 position = vec3(aPos.x, aPos.y + jumpHeight, aPos.z);
		gl_Position = perspective * view  * model * vec4(position, 1);
	} 
	else if (animation == testAnimation) 
	{
		gl_Position = perspective * view * positivePivotMatrix * model * negativePivotMatrix * vec4(aPos, 1);
	}
	else
	{
		gl_Position = perspective * view * model * vec4(aPos, 1);
	}
}