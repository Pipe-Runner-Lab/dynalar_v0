#version 330

in vec2 v_uv;
out vec4 colour;

uniform sampler2D u_Texture;

void main() {
	colour = texture(u_Texture, v_uv);
}