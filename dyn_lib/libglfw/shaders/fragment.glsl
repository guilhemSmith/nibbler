#version 400 core
out vec4 frag_color;

in vec3 frag_pos;
in vec3 frag_normal;

uniform vec3 base_color;
// uniform vec3 light_pos; 

void main() {
	vec3 norm = normalize(frag_normal);
	vec3 light_dir = normalize((vec3(1.0, 2.0, 3.0) + frag_pos) - frag_pos);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * vec3(1.0);
	vec3 result = (0.3 + diffuse) * base_color;
	frag_color = vec4(result, 1.0);
}