#version 330 core

in vec2 texCoords;
out vec4 fragmentColor;

uniform sampler2D baseTexture;

void main(){
	fragmentColor = texture(baseTexture, texCoords);
}
