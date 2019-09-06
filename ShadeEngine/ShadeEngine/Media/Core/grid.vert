#version 330 core

uniform mat4 mv;
uniform mat4 proj;

in vec3 vColour;
in vec3 vVert;

out vec4 fColour;

void main(void){
	fColour = vec4(vColour, 1.0f);

	gl_Position = proj * mv * vec4(vVert, 1.0f);
}