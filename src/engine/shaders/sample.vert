#version 330

layout (location = 0) in vec3 pos;
	
out vec3 vColor;

void main() {
	vColor = clamp(pos, 0.0f, 1.0f);
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
}