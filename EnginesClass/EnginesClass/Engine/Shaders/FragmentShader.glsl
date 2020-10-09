#version 450 core
in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

struct Light {
	vec3 lightPos;
	float ambient;
	float diffuse;
	vec3 lightColour;
};

	uniform sampler2D inputTexture;
	uniform vec3 viewPosition;
	uniform Light light;

void main() {

	vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.lightColour;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPosition);
    float diff = max(dot(norm,lightDir), 0.0);
    vec3 diffuse = diff*texture(inputTexture, TexCoords).rgb*light.lightColour;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.lightColour;

    vec3 result = ambient + diffuse + specular;
    fColour = vec4(result, 1.0f);
}