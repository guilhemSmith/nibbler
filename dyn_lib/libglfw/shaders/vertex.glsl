#version 400 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

out vec3 frag_pos;
out vec3 frag_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// frag_pos = vec3(view * model * vec4(a_pos, 1.0));
	// gl_Position = projection * view * model * vec4(a_pos, 1.0);
	frag_pos = a_pos;
	frag_normal = a_normal;
	gl_Position = projection * view * model * vec4(a_pos, 1.0);
}