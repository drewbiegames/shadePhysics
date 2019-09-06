#version 330 compatibility

in vec2 vVertex;
in vec2 vTexCoord;

out vec2 fTexCoord;

void main(){
	fTexCoord = vTexCoord;

	gl_Position = vec4(vVertex.x, vVertex.y, 0.01f, 1.0f);
}