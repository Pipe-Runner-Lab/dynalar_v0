#version 330

struct DirectionalLight{
	// vec3 color acts as a RBG filter, 
	// eg: (1, 0, 0) means red channel is allowed  to show up in output frag color
	vec3 color; 
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

in vec2 v_uv;
in vec3 v_normal;
out vec4 colour;

uniform sampler2D u_Texture;
uniform DirectionalLight u_directionalLight;

void main() {
	vec4 ambientColor = vec4(u_directionalLight.color * u_directionalLight.ambientIntensity, 1.0f);

	 // max to clip value below 0, ie. source is below surface
	float diffuseFactor = max(dot(normalize(v_normal), normalize(u_directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(u_directionalLight.color * u_directionalLight.diffuseIntensity * diffuseFactor, 1.0f);

	colour = texture(u_Texture, v_uv) * (ambientColor + diffuseColor);
}