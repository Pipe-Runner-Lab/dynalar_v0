#version 330

out vec4 colour;
in vec3 v_Color;

void main() {
	colour = vec4(v_Color, 1.0);
}
