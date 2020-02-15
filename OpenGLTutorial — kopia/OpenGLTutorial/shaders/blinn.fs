#version 330

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

struct SpotLightInfo
{
    vec4 position;
    vec3 intensity;
    vec3 direction;
    float exponent;
    float cutoff;
};

uniform SpotLightInfo Spot;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

uniform vec3 ViewPosition;

uniform sampler2D texture_diffuse1;

layout( location = 0 ) out vec4 FragColor;

float attenuation(float dist)
{
    return 1 + 0.007 * dist + 0.0002 * dist * dist;
}

vec3 ads()
{
    // return Normal;
    vec4 objectColor4 = texture(texture_diffuse1, TexCoords);
    if(objectColor4.a<0.7)
        discard;
    vec3 objectColor = vec3(objectColor4);

    vec3 ambient = Ka;
    vec3 specular = vec3(0);
    vec3 diffuse = vec3(0);

    // reflector

    vec3 lightDirection = normalize( vec3( Spot.position ) - Position );
    float angle = acos( dot(-lightDirection, Spot.direction) );
    float cutoff = radians( clamp( Spot.cutoff, 0, 90 ) );

    //if (angle < cutoff)
    //{
        //float spotFactorSpecular = pow( dot(-lightDirection, Spot.direction), Spot.exponent);
        //float spotFactor = cutoff-angle;
        //float lightDistance = length( vec3( Spot.position ) - Position);
        //vec3 spotFinalIntensity = spotFactor * Spot.intensity / attenuation(lightDistance);
        //vec3 spotFinalIntensitySpecular = spotFactorSpecular * Spot.intensity / attenuation(lightDistance);
            
        vec3 viewDirection = normalize(ViewPosition - vec3(Position));
        
        vec3 h = normalize(lightDirection + viewDirection);
        specular += Ks * pow(max(dot(h, Normal), 0), Shininess);
        
        diffuse += Kd * max(dot(lightDirection, Normal), 0);

        //specular += Ks * pow(max(dot(viewDirection, reflect(-lightDir, norm)), 0), Shininess);
        
        //diffuse += Kd * max(dot(Normal, lightDirection), 0);
    //}

    return clamp(objectColor * (ambient + specular + diffuse), 0, 1);
}

void main()
{
    vec4 c = vec4(ads(), 1);
    FragColor = c;
}