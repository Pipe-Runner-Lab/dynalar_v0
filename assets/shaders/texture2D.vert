#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
	v_texCoord = texCoord;
}