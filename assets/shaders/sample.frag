#version 330

// in vec2 v_texCoord;
in vec3 v_my_color;
out vec4 colour; // only possible output from fragment shader, so name not important

uniform vec4 u_color;
uniform sampler2D u_Texture;

void main() {
	// vec4 texColor = texture(u_Texture, v_texCoord);
	// colour = texColor + vec4(0.5f, 0.0f, 0.0f, 1.0f);
	colour = vec4(v_my_color, 1.0f);
}