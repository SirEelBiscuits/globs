#version 150

in vec4 colour_from_vshader;
out vec4 out_colour;

void main() {
	out_colour = colour_from_vshader;
}

