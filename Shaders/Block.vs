#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in mat4 model;

out vec2 texCoords;

uniform mat4 projection, view;

void main(){
	gl_Position = projection * view * model * vec4(vertexPos, 1.0);
	texCoords = aTexCoords;
}
