#version 330

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

struct SpotLight
{
    vec4 position;
    vec3 intensity;
    vec3 direction;
    float cutoff;
};

uniform bool blinn;

uniform SpotLight[5] Lights;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

uniform vec3 ViewPosition;

uniform sampler2D texture_diffuse1;

layout(location = 0) out vec4 FragColor;

float attenuation(float d)
{
    return 1 + 0.008 * d + 0.0004 * d * d;
}

void main()
{
    vec4 objectColor4 = texture(texture_diffuse1, TexCoords);
    if (objectColor4.a < 0.7) discard;
    vec3 objectColor = vec3(objectColor4);

    vec3 ambient = Ka;
    vec3 specular = vec3(0);
    vec3 diffuse = vec3(0);

    // all light sources
    for (int i = 0; i < 5; i++)
    {
        vec3 lightDir = normalize(vec3(Lights[i].position) - Position);
        float angle = acos(dot(-lightDir, Lights[i].direction));
        float cutoff = radians(Lights[i].cutoff);

        if (angle < cutoff || i == 4) // last light is point light
        {
            float lightDist = length(vec3(Lights[i].position) - Position);
            vec3 spotInt = Lights[i].intensity / attenuation(lightDist);
            
            vec3 viewDir = normalize(ViewPosition - vec3(Position));

            diffuse += spotInt * Kd * max(dot(lightDir, Normal), 0);
            
            if (blinn)
            {
                vec3 halfDir = normalize(lightDir + viewDir);
                specular += spotInt * Ks * pow(max(dot(halfDir, Normal), 0), Shininess);
            }
            else
            {
                vec3 reflectDir = reflect(-lightDir, Normal);
                float reflectAngle = max(dot(reflectDir, viewDir), 0);
                specular += spotInt * Ks * pow(reflectAngle, Shininess);
            }
        }
    }

    FragColor = vec4(clamp(objectColor * (ambient + specular + diffuse), 0, 1), 1);
}