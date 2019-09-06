#version 330 compatibility

uniform mvp;

in vec3 vColor;
in vec3 vVertex;

out vec3 fColor;

void main(){
	gl_Position = mvp * vec4(vVertex, 1);

	fColor = vColor;
}