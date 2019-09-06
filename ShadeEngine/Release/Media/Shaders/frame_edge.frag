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
		-1.0f,  -2.0f, -1.0f,
		-2.0f,  12.0f, -2.0f,
		-1.0f,  -2.0f, -1.0f
	);

	vec3 sample[9];
	vec3 col = vec3(0.0f);

	for(int i = 0; i < 9; i++){
		sample[i] = vec3(texture(fFrame, fTexCoord.st + offsets[i]));
		col += sample[i] * kernel[i];
	}

	vec3 tex = vec3(texture(fFrame, fTexCoord));
	float greyscale = (col.x * 0.75 + col.y * 0.75 + col.z * 0.75)  / 3;
	if(greyscale > 0.5){
		tex = vec3(0.0f);
	}

	gl_FragColor = vec4(tex, 1.0f);
}