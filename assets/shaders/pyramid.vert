#version 330

layout (location = 0) in vec3 pos;
	
out vec3 v_Color;

// uniform mat4 model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
	v_Color = clamp(pos, 0.0f, 1.0f);
	gl_Position = u_projection * u_view * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
}