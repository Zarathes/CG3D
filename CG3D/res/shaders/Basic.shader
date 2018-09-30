#shader vertex
#version 460 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform uint materialID;

// Materials
struct Material
{
	uint matID;			// 4 Bytes
	int  matType;		// 4 Bytes	
	float weight;		// 4 Bytes
	float roughness;	// 4 Bytes

	vec4 diffuse;		// 16 Bytes

	float specular;		// 4 Bytes
	float refraction;	// 4 Bytes
	float attentuate;	// 4 Bytes
	float flux;			// 4 Bytes

	float glow;			// 4 Bytes
	float unit;			// 4 Bytes
	float plastic;		// 4 Bytes
	float padding;		// 4 Bytes

};

layout(std430, binding = 0) buffer MaterialBuffer
{
	Material materials[];
} materialBuffer;

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec3 f_pos;
out vec4 f_color;
out vec3 f_normal;

void main() 
{
	gl_Position = (proj * view * model) * position;
	f_pos = vec3(model * position);
	f_color = materialBuffer.materials[materialID].diffuse;
	f_normal = mat3(transpose(inverse(model))) * normal;
};

#shader fragment
#version 460 core

// Directional Light
struct  DirectionalLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
};

uniform float alpha;
uniform float ambientStrength;
uniform float specularStrength;
uniform DirectionalLight dirLight;
uniform vec3 viewPos;

in vec3 f_pos;
in vec4 f_color;
in vec3 f_normal;

out vec4 out_color;

void main() 
{
	// ambient
	vec3 ambient = ambientStrength * dirLight.color;

	// diffuse
	vec3 norm = normalize(f_normal);
	vec3 lightDir = normalize(dirLight.position - f_pos);
	float diff = max(dot(norm, dirLight.direction), 0.0);
	vec3 diffuse = diff * dirLight.color;

	// specular
	vec3 viewDir = normalize(viewPos - f_pos);
	vec3 reflectDir = reflect(-dirLight.direction, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * dirLight.color;

	vec3 result = (ambient + diffuse) * f_color.xyz;
	out_color = vec4(result, alpha);
};