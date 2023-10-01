#version 330

in vec2 v_texCoord;
out vec4 colour; // only possible output from fragment shader, so name not important

uniform vec4 u_color;
uniform sampler2D u_Texture;

void main() {
	vec4 texColor = texture(u_Texture, v_texCoord);
	colour = texColor;
}