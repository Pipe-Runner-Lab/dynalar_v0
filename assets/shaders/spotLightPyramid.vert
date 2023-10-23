#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in float texSlot;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;
	
out vec2 v_uv;
out vec3 v_normal;
out vec3 v_surface_coord;
flat out int v_texSlot;

// uniform mat4 model;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
	v_uv = uv;

	// mat3 will drop the last row and column
	// transpose and inverse will make this operation scale invariant
	v_normal = mat3(transpose(inverse(u_model))) * normal; 
	// the light should not depend on camera transform and projection has no role here
	v_surface_coord = (u_model * vec4(pos, 1.0)).xyz; // swizzle
	v_texSlot = int(texSlot);

	gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
}