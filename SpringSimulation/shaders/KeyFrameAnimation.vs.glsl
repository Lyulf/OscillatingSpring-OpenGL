#version 330 core

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec3 InNormal;
layout(location = 2) in vec2 InTextureCoord;
layout(location = 3) in vec3 InNextPosition;
layout(location = 4) in vec3 InNextNormal;

out vec3 Color;
out vec2 TextureCoord;

uniform mat4 ProjectionModelViewMatrix;
uniform float TweenFactor;

void main() {
	vec4 Position = vec4(mix(InPosition, InNextPosition, TweenFactor), 1.0f);
	gl_Position = ProjectionModelViewMatrix * Position;
	Color = vec3(1.0f, 1.0f, 1.0f);
	TextureCoord = InTextureCoord;
}