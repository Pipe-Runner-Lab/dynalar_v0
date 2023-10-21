#version 330

struct DirectionalLight{
	// vec3 color acts as a RBG filter, 
	// eg: (1, 0, 0) means red channel is allowed  to show up in output frag color
	vec3 color; 
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
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
uniform Material u_material_0;
uniform vec3 u_eyePos; // position of camera, used for reflection

void main() {
	vec4 ambientColor = vec4(u_directionalLight.color * u_directionalLight.ambientIntensity, 1.0f);

	 // max to clip value below 0, ie. source is below surface
	float diffuseFactor = max(dot(normalize(v_normal), normalize(u_directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(u_directionalLight.color * u_directionalLight.diffuseIntensity * diffuseFactor, 1.0f);

	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	// only compute specular if light is making less 180deg with surface
	if(diffuseFactor > 0.0f){
		vec3 eyeFromSurface = normalize(u_eyePos - v_surface_coord);
		vec3 reflectedFromSurface = normalize(reflect(u_directionalLight.direction, normalize(v_normal)));

		float specularFactor = dot(eyeFromSurface, reflectedFromSurface);

		if(specularFactor > 0.0f){
			specularFactor = pow(specularFactor, u_material_0.shininess);
			specularColor = vec4(u_directionalLight.color * u_material_0.specularIntensity * specularFactor, 1.0f);
		}
	}

	colour = texture(u_Texture, v_uv) * (ambientColor + diffuseColor + specularColor);
}