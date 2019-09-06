#version 330 compatibility

uniform vec4 fLight0_Ambient;
uniform vec4 fLight0_Diffuse;
uniform vec4 fLight0_Specular;

uniform sampler2D fMainTexture;
in vec2 fUV;

in float fDiffuseIntensity;
in float fSpecularIntensity;
in float fSpecularReflection;

uniform float fTime;
uniform float fMaxTime;
uniform float fBurnStep; //small value to diffine the orange part

vec4 lerp(vec4 start, vec4 end, float percent){
	return start * percent * (end - start);
}

void main(void)
{
	vec4 tex = texture(fMainTexture, fUV); //texture colour

	//calculate time (decimal percentage) for a cut off
	float time = fTime / fMaxTime;

	//transparency cut off
	if(tex.a < time){
		discard; //does not render this fragment
	}
	else if (tex.a - fBurnStep < time){
		tex = vec4(1.0f, 0.1f, 0.00f, 1.0f);
	}
	else if (tex.a - fBurnStep * 5 < time){
		//lerp black to texture colour
		float min = tex.a - fBurnStep * 5;
		float max = tex.a - fBurnStep;
		float percent = (tex.a - min) / (max - min);
		
		tex = lerp(vec4(tex.xyz, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f), percent);
	}
	
	//Setting Light Colours
	vec4 amb = fLight0_Ambient;
	vec4 dif = fLight0_Diffuse * fDiffuseIntensity;
	vec4 spc = fLight0_Specular * fSpecularIntensity * fSpecularReflection;
	
	//if it is not discarded then alpha is 1;
	tex.a = 1.0f;

	vec4 finalCol = ((amb + dif + spc) * 0.33) * tex;
	gl_FragColor = finalCol;
}