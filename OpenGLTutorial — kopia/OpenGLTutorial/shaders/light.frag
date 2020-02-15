#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3  direction;
    float cutOff;
	float outerCutOff;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


uniform vec3 ambientLight;
uniform Light light1;
uniform Light light2;
uniform Light light3;
uniform Material material;
uniform vec3 viewPos;

uniform bool wBall;

in vec3 fragPos;
in vec3 normal;
in vec2 uv;

vec3 calcDirLight(Light light)
{
vec3 diffuseC;
vec3 specC;
	if(!wBall)
	{
		diffuseC = vec3(texture(material.diffuse, uv));
		specC = vec3(texture(material.specular, uv));
	}
	else
	{
		diffuseC = vec3(1.0,1.0,1.0);
		specC = vec3(1.0,1.0,1.0);
	}

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    		    light.quadratic * (distance * distance));



    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff *  diffuseC);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * specC);
    diffuse  *= intensity;
	specular *= intensity;
    vec3 ambient = ambientLight *  diffuseC;
    diffuse  *= attenuation;
    specular *= attenuation;
	ambient *= attenuation;
    return diffuse + specular + ambient;
}

void main()
{

	{
    vec3 result = calcDirLight(light1);
    result = result + calcDirLight(light2);
    result = result + calcDirLight(light3);
    FragColor = vec4(result, 1.0);
	}
}