#version 450 core

struct LightArguments {
	vec3 position;
	vec3 color;
	float strength;
};

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform LightArguments[] lightArgs;
uniform int lightAmount;
uniform vec3 cameraPos;

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightArgs[0].color;
    FragColor = texture(texture1, TexCoord);
}