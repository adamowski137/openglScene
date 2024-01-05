#version 450 core

in vec4 fragmentPosition;
in vec3 fragmentNormal;
in vec3 teColor;


uniform vec3 tint;
uniform sampler2D texture1;

out vec4 finalColor;

void main()
{
    finalColor = vec4(teColor, 1.0f);
}
