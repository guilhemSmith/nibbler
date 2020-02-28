#version 400 core
out vec4 frag_color;

in vec3 frag_pos;

uniform vec3 base_color;

void main() {
	frag_color = vec4(base_color, 1.0);
}