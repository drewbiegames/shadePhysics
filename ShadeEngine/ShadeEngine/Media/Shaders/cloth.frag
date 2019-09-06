#version 330 compatibility

uniform sampler2D fMainTex;

in vec2 fUV;

void main(){
	vec4 texColour = texture(fMainTex, fUV);
	
	gl_FragColor = texColour;
}