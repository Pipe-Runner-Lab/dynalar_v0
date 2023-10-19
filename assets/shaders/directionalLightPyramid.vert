#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
	
out vec2 v_uv;
out vec3 v_normal;

// uniform mat4 model;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
	v_uv = uv;

	// mat3 will drop the last row and column
	// transpose and inverse will make this operation scale invariant
	v_normal = mat3(transpose(inverse(u_model))) * normal; 

	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
}