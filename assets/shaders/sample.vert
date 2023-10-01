#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main() {
	gl_Position = vec4(pos, 1.0);
	v_texCoord = texCoord;
}