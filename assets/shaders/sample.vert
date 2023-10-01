#version 330

layout (location = 0) in vec3 pos;
// layout (location = 1) in vec2 texCoord;
layout (location = 1) in vec3 my_color;

// out vec2 v_texCoord;
out vec3 v_my_color;

// out vec4 vColor;

void main() {
	gl_Position = vec4(pos, 1.0);
	// v_texCoord = texCoord;
	v_my_color = my_color;
}