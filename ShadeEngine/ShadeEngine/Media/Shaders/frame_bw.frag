#version 330 compatibility

in vec2 fTexCoord;

uniform sampler2D fFrame;

void main(){
	vec4 color = texture(fFrame, fTexCoord);
	float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;

	gl_FragColor = vec4(average, average, average, 1.0);
}