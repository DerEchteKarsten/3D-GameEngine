#version 330 core
out vec4 FragColor;
  
in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D Texture0;
uniform vec3 LightPos;
uniform vec3 camPos;
 

vec4 lightColor = vec4(1, 1, 1, 1);
 
vec4 pointLight()
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = LightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(Texture0, TexCoord) * (diffuse * inten + ambient) + specular * inten) * lightColor;
}

void main()
{
    FragColor = pointLight() * 2;
}

