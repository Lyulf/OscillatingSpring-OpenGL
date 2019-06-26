#version 330 core

in vec2 TextureCoord;
in vec3 Color;

out vec4 FragColor;

uniform sampler2D Texture[8];

uniform float TweenFactor;

void main() {
	//if(gl_FrontFacing) {
		FragColor = texture(Texture[0], TextureCoord) * vec4(Color, 1.0f);
	//}
}