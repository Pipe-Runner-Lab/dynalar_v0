#version 330

const int MAX_POINT_LIGHT = 3;

struct BaseLight {
	vec3 color; 
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight{
	// vec3 color acts as a RBG filter, 
	// eg: (1, 0, 0) means red channel is allowed  to show up in output frag color
	BaseLight base;
	vec3 direction;
};

struct Attenuation {
	float exponent_coef;
	float linear_coef;
	float constant_coef;
};

struct PointLight{
	BaseLight base;
	vec3 position;
	Attenuation attenuation;
};

// an object can have multiple materials
struct Material{
	float specularIntensity; 
	float shininess;
};

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_surface_coord;
out vec4 colour;

uniform sampler2D u_Texture;
uniform DirectionalLight u_directionalLight;
uniform int u_num_pointLights;
uniform PointLight u_pointLightArray[MAX_POINT_LIGHT];
uniform Material u_material_0;
uniform vec3 u_eyePos; // position of camera, used for reflection

vec4 CalculateLightViaDirection(BaseLight light, vec3 direction){
	vec4 ambientColor = vec4(light.color * light.ambientIntensity, 1.0f);

	 // max to clip value below 0, ie. source is below surface
	float diffuseFactor = max(dot(normalize(v_normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	// only compute specular if light is making less 180deg with surface
	if(diffuseFactor > 0.0f){
		vec3 eyeFromSurface = normalize(u_eyePos - v_surface_coord);
		vec3 reflectedFromSurface = normalize(reflect(direction, normalize(v_normal)));

		float specularFactor = dot(eyeFromSurface, reflectedFromSurface);

		if(specularFactor > 0.0f){
			specularFactor = pow(specularFactor, u_material_0.shininess);
			specularColor = vec4(light.color * u_material_0.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColor + diffuseColor + specularColor);
}

vec4 CalculateDirectionalLight(DirectionalLight directionalLight) {
	return CalculateLightViaDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalculatePointLight(PointLight pointLight, vec3 suface_coord) {
	vec3 direction = normalize(suface_coord - pointLight.position);
	float dist = length(suface_coord - pointLight.position);
	float attenuation = pow(dist, 2) * pointLight.attenuation.exponent_coef + 
	dist * pointLight.attenuation.linear_coef + 
	pointLight.attenuation.constant_coef; // ax^2 + bx + c
	return CalculateLightViaDirection(pointLight.base, direction) / attenuation; // 1/att
}

void main() {
	vec4 finalColor = CalculateDirectionalLight(u_directionalLight);
	for(int i = 0; i < u_num_pointLights; i++){
		finalColor += CalculatePointLight(u_pointLightArray[i], v_surface_coord);
	}

	colour = texture(u_Texture, v_uv) * finalColor;
}