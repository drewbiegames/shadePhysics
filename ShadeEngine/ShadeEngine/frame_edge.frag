#version 330 compatibility

in vec2 fTexCoord;

uniform sampler2D fFrame;

uniform float fOffset;

void main(){

	vec2 offsets[9] = vec2[](
		vec2(-fOffset, fOffset),
		vec2(0.0f,	   fOffset),
		vec2(fOffset,  fOffset),
		vec2(-fOffset, 0.0f),
		vec2(0.0f,	   0.0f),
		vec2(fOffset,  0.0f),
		vec2(fOffset,  -fOffset),
		vec2(0.0f,     -fOffset),
		vec2(fOffset,  -fOffset)
	);

	float kernel[9] = float[](
		0.0f,  1.0f, 0.0f,
		1.0f,  -4.0f, 1.0f,
		0.0f,  1.0f, 0.0f
	);

	vec3 sample[9];
	vec3 col = vec3(0.0f);

	for(int i = 0; i < 9; i++){
		sample[i] = vec3(texture(fFrame, fTexCoord.st + offsets[i]));
		col += sample[i] * kernel[i];
	}

	vec4 tex = texture(fFrame, fTexCoord);
	vec4 edge = tex + (vec3(1.0f) - vec4(col, 1.0f)) / 2;

	gl_FragColor = edge;
}