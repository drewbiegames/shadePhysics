#version 330 compatibility

in vec2 fTexCoord;

uniform sampler2D fFrame;

void main(){
	gl_FragColor = vec4(vec3(1.0 - texture(fFrame, fTexCoord)), 1.0);
}