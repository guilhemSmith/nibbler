#version 400 core
layout (location = 0) in vec3 a_pos;

out vec3 frag_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// frag_pos = vec3(view * model * vec4(a_pos, 1.0));
	// gl_Position = projection * view * model * vec4(a_pos, 1.0);
	frag_pos = a_pos;
	gl_Position = projection * view * model * vec4(a_pos, 1.0);
}