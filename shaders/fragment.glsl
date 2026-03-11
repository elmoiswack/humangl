#version 410 core

flat in int currentIndex;

out vec4 fragmentColor;

uniform vec3 headColor;
uniform vec3 torsoColor;
uniform vec3 armLeftColor;
uniform vec3 armRightColor;
uniform vec3 legLeftColor;
uniform vec3 legRightColor;

void main() 
{
	int sizePerPart = 72;

	if (currentIndex < sizePerPart) 
	{
		fragmentColor = vec4(headColor, 1);
	} 
	else if (currentIndex < (sizePerPart * 2)) 
	{
		fragmentColor = vec4(torsoColor, 1);
	} 
	else if (currentIndex < (sizePerPart * 3)) 
	{
		fragmentColor = vec4(armLeftColor, 1);
	} 
	else if (currentIndex < (sizePerPart * 4)) 
	{
		fragmentColor = vec4(armRightColor, 1);
	} 
	else if (currentIndex < (sizePerPart * 5)) 
	{
		fragmentColor = vec4(legLeftColor, 1);
	} 
	else if (currentIndex < (sizePerPart * 6)) 
	{
		fragmentColor = vec4(legRightColor, 1);
	}
}