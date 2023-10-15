#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
	
out vec2 v_uv;

// uniform mat4 model;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
	v_uv = uv;
	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
}