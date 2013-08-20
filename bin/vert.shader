#version 150

in vec4 position;
in vec4 colour;
out vec4 colour_from_vshader;

void main() {
	gl_Position = position;
	colour_from_vshader = colour;
}
