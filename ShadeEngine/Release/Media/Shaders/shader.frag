#version 330 compatibility

uniform vec4 fLight0_Ambient;
uniform vec4 fLight0_Diffuse;
uniform vec4 fLight0_Specular;

uniform sampler2D fMainTexture;
in vec2 fUVcoord;

in float fDiffuseIntensity;
in float fSpecularIntensity;
in float fSpecularReflection;

void main(void)
{
	vec4 amb = fLight0_Ambient;
	vec4 dif = fLight0_Diffuse * fDiffuseIntensity;
	vec4 spc = fLight0_Specular * fSpecularIntensity * fSpecularReflection;
	vec4 tex = texture(fMainTexture, fUVcoord);

	vec4 finalCol = tex + ((amb + dif + spc) * 0.33);
	
    gl_FragColor = finalCol;
}