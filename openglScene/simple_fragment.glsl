#version 450 core

float ambientStrength = 0.1;
float specularStrength = 0.5;

struct LightArguments {
	vec3 position;
	vec3 color;
	float strength;
};

struct ReflectorArguments {
    vec3 position;
    vec3 color;
    float cutOff;
    vec3 direction;
};

uniform ReflectorArguments leftReflector;
uniform ReflectorArguments rightReflector;

uniform LightArguments[8] lightArgs;
uniform int lightAmount;
uniform int lightingModel;
uniform vec3 cameraPos;
uniform vec3 theme;


out vec4 FragColor;

in vec3 global_normal;
in vec3 global_position;

in vec3 oColor;
flat in vec3 flatColor;

vec3 getReflectorComponent();
vec3 getPhongLightingModel();
vec3 getFogComponent(vec3 result);

void main()
{
    vec3 color = oColor;
    if (lightingModel == 0)
    {
        color = getPhongLightingModel();
    }
    if (lightingModel == 2)
    {
        color = flatColor;
    }
    FragColor = vec4(color, 1.0f);
}

vec3 getReflectorComponent()
{
    float distanceLeft = length(leftReflector.position - global_position);
    float distanceRight = length(rightReflector.position - global_position);
    float attenuationLeft = 1.0 / (1 + 0.1 * distanceLeft + 0.032 * distanceLeft * distanceLeft);
    float attenuationRight = 1.0 / (1 + 0.1 * distanceRight + 0.032 * distanceRight * distanceRight);
    vec3 ambient = ambientStrength * (leftReflector.color + rightReflector.color);
    vec3 norm = normalize(global_normal);
    vec3 lightDirLeft = normalize(leftReflector.position - global_position);
    vec3 lightDirRight = normalize(rightReflector.position - global_position);
    float thetaLeft = dot(lightDirLeft, normalize(leftReflector.direction));
    float thetaRight = dot(lightDirRight, normalize(rightReflector.direction));
    float intensityLeft = clamp(thetaLeft - leftReflector.cutOff, 0.0, 1.0);
    float intensityRight = clamp(thetaRight - rightReflector.cutOff, 0.0, 1.0);

    float diffLeft = max(dot(norm, lightDirLeft), 0.0);
    float diffRight = max(dot(norm, lightDirRight), 0.0);
    vec3 diffuse = attenuationLeft * intensityLeft * diffLeft * leftReflector.color + attenuationRight * intensityRight * diffRight * rightReflector.color;

    vec3 viewDir = normalize(cameraPos - global_position);

    vec3 reflectDirLeft = reflect(-lightDirLeft, norm);
    vec3 reflectDirRight = reflect(-lightDirRight, norm);
    float specLeft = pow(max(dot(viewDir, reflectDirLeft), 0.0), 32);
    float specRight = pow(max(dot(viewDir, reflectDirRight), 0.0), 32);
    vec3 specularLeft = specularStrength * specLeft * leftReflector.color;
    vec3 specularRight = specularStrength * specRight * rightReflector.color;

    return ambient + diffuse + attenuationLeft * intensityLeft * specularLeft + attenuationRight * intensityRight * specularRight;
}

vec3 getPhongLightingModel()
{
    vec3 viewDir = normalize(cameraPos - global_position);
    vec3 result = vec3(0, 0, 0);
    for (int i = 0; i < lightAmount; i++)
    {
        vec3 ambient = ambientStrength * lightArgs[i].color;

        vec3 norm = normalize(global_normal);
        vec3 lightDir = normalize(lightArgs[i].position - global_position);
        float diff = max(dot(norm, lightDir), 0);
        vec3 diffuse = diff * lightArgs[i].color;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightArgs[i].color;
        float distance = length(lightArgs[i].position - global_position);
        float attenuation = 1.0 / (1 + 0.1 * distance + 0.032 * distance * distance);

        result += attenuation * (ambient + diffuse + specular);
    }

    result += getReflectorComponent();


    result *= oColor;

    return getFogComponent(result);
}

vec3 getFogComponent(vec3 result)
{
    float dist = length(global_position - cameraPos);
    float fogFactor = exp(-0.01 * dist * dist);
    fogFactor = 1 - clamp(fogFactor, 0.0, 1.0);
    vec3 fogColor = theme;
    return mix(result, fogColor, fogFactor);
}