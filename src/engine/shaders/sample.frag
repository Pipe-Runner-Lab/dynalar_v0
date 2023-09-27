#version 330

out vec4 colour; // only possible output from fragment shader, so name not important
in vec3 vColor;

void main() {
	colour = vec4(vColor, 1.0);
}