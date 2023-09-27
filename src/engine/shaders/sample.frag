#version 330

out vec4 colour; // only possible output from fragment shader, so name not important
in vec4 vColor;

void main() {
	colour = vColor;
}