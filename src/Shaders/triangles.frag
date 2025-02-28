// Fragment Shader
#version 460 core

layout (location = 0) out vec4 fColor;

in vec4 vColor;

void main() {
	fColor = vec4(vColor);
}