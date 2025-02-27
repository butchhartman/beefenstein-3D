// Vertex Shader
#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 Color;

out vec4 vColor;

void main(){
	gl_Position = vPosition;
	vColor = vec4(Color, 1.0f);
}