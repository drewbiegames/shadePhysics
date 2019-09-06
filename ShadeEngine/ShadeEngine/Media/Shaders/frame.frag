#version 330 compatibility

in vec2 fTexCoord;

uniform sampler2D fFrame;

void main(){
	gl_FragColor = texture(fFrame, fTexCoord);
}