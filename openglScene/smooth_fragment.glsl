#version 450 core

struct LightArguments {
	vec3 position;
	vec3 color;
	float strength;
};

in vec4 fragmentPosition;
in vec3 fragmentNormal;
in vec3 teColor;


uniform sampler2D texture1;
uniform int lightAmount;
uniform LightArguments[8] lightArgs;
uniform vec3 cameraPos;

out vec4 finalColor;

vec3 getPhongColorModel();

void main()
{
	vec3 result = getPhongColorModel();
    finalColor = vec4(result, 1.0f);
}


vec3 getPhongColorModel()
{
    float ambientStrength = 0.1;
	float specularStrength = 0.5;
    vec3 result = vec3(0, 0, 0);
    for(int i = 0; i < lightAmount; i++)
    {
        vec3 ambient = ambientStrength * lightArgs[i].color;

	    vec3 norm = normalize(fragmentNormal);
        vec3 lightDir = normalize(lightArgs[i].position - fragmentPosition.xyz);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightArgs[i].color;

        vec3 viewDir = normalize(cameraPos - fragmentPosition.xyz);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightArgs[i].color; 

        result += (ambient + diffuse + specular) * teColor;
    }

    return result;
}