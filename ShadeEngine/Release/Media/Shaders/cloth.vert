#version 330 compatibility

uniform mat4 mvp;

in vec3 vVertex;
in vec2 vUV;

out vec2 fUV;

void main(void){

	gl_Position =  mvp * vec4(vVertex, 1.0);

	fUV = vUV;
}