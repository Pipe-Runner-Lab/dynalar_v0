#version 330

struct AmbientLight{
	vec3 color;
	float intensity;
};

in vec2 v_uv;
out vec4 colour;

uniform sampler2D u_Texture;
uniform AmbientLight u_ambientLight;

void main() {
	vec4 ambientColor = vec4(u_ambientLight.color, 1.0f) * u_ambientLight.intensity;
	colour = texture(u_Texture, v_uv) * ambientColor;
}