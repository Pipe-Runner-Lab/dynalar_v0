#version 330

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_surface_coord;
flat in int v_texSlot;
out vec4 colour;

const int MAX_POINT_LIGHT = 3;
const int MAX_SPOT_LIGHT = 3;

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

struct SpotLight{
	BaseLight base;
	vec3 position;
	vec3 direction;
	float coneAngle;
	Attenuation attenuation;
};

// an object can have multiple materials
struct Material{
	float specularIntensity; 
	float shininess;
};

uniform sampler2D u_Texture[2];
uniform DirectionalLight u_directionalLight;
uniform int u_num_pointLights;
uniform int u_num_spotLights;
uniform PointLight u_pointLightArray[MAX_POINT_LIGHT];
uniform SpotLight u_spotLightArray[MAX_SPOT_LIGHT];
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

vec4 CalculatePointLight(PointLight pointLight) {
	vec3 diff = v_surface_coord - pointLight.position;
	vec3 direction = normalize(diff);
	float distance_from_surface = length(diff);
	float attenuation = (
		distance_from_surface * distance_from_surface * pointLight.attenuation.exponent_coef + 
		distance_from_surface * pointLight.attenuation.linear_coef + 
		pointLight.attenuation.constant_coef
	); // ax^2 + bx + c
	return CalculateLightViaDirection(pointLight.base, direction) / attenuation; // 1/att
}

vec4 CalculateSpotLight(SpotLight spotLight) {
	vec3 rayDirection = normalize(v_surface_coord - spotLight.position);
	float spotLightFactor = dot(rayDirection, spotLight.direction);

	if(spotLightFactor > spotLight.coneAngle){
		vec4 color = CalculatePointLight(
			PointLight(
				spotLight.base,
				spotLight.position,
				spotLight.attenuation
			)
		);
		return color * (1.0f - (1.0f - spotLightFactor) * (1 / (1.0f - spotLight.coneAngle)));
	}

	return vec4(0.0, 0.0, 0.0, 1.0);
}

void main() {
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0);
	finalColor.xyz += CalculateDirectionalLight(u_directionalLight).xyz;
	for(int i = 0; i < u_num_pointLights; i++){
		finalColor.xyz += CalculatePointLight(u_pointLightArray[i]).xyz;
	}
	for(int i = 0; i < u_num_spotLights; i++){
		finalColor.xyz += CalculateSpotLight(u_spotLightArray[i]).xyz;
	}

	colour = texture(u_Texture[v_texSlot], v_uv) * finalColor;
}