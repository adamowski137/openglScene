#version 450 core

uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform vec3 theme;

in vec3 global_position;

out vec4 FragColor;

vec3 getFogComponent(vec3 result);

void main()
{
    FragColor = vec4(getFogComponent(lightColor), 1.0f);
}

vec3 getFogComponent(vec3 result)
{
    float dist = length(global_position - cameraPos);
    float fogFactor = exp(-0.01 * dist * dist);
    fogFactor = 1 - clamp(fogFactor, 0.0, 1.0);
    vec3 fogColor = theme;
    return mix(result, fogColor, fogFactor);
}