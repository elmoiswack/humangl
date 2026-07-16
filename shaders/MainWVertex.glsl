#version 430 core
layout(location = 0) in vec3 aPos;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;
uniform mat4 positivePivotMatrix;
uniform mat4 negativePivotMatrix;

uniform int animation;
uniform float jumpHeight;

layout(std430, binding = 0) buffer DebugBuffer
{
    vec4 inputPos[];
};

layout(std430, binding = 1) buffer OutputBuffer
{
    vec4 outputPos[];
};

void main()
{
    const int walkingAnimation = 1;
    const int jumpAnimation = 2;
    const int runAnimation = 3;
    const int tposeAnimation = 4;
    const int flexAnimation = 5;

    inputPos[gl_VertexID] = vec4(aPos, 1.0);

    if (animation == walkingAnimation || animation == runAnimation || animation == tposeAnimation || animation == flexAnimation)
    {
        gl_Position = perspective * view * positivePivotMatrix * model * negativePivotMatrix * vec4(aPos, 1.0);
    }
    else if (animation == jumpAnimation)
    {
        vec3 position = vec3(aPos.x, aPos.y + jumpHeight, aPos.z);
        gl_Position = perspective * view * model * vec4(position, 1.0);
    }
    else
    {
        gl_Position = perspective * view * model * vec4(aPos, 1.0);
    }

    outputPos[gl_VertexID] = gl_Position;
}