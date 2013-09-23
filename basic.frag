#version 150

in vec4 colour_from_vshader;
in vec2 texture_from_vshader;
out vec4 out_colour;

uniform sampler2D texture_sampler;

void main() {
	out_colour = colour_from_vshader * texture(texture_sampler, texture_from_vshader);
