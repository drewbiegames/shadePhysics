#version 330 compatibility

uniform mat4 mvp;
uniform vec3 view;

in vec3 vVertex;
in vec2 vUV;
in vec3 vNormal;

uniform vec4 vLight0_Direction;

out float fDiffuseIntensity;
out float fSpecularIntensity;
out float fSpecularReflection;

out vec2 fUVcoord;

void main(void){
	//Excute Light Calculations
	//Precalculations
	vec3 normDir = normalize(vNormal);
	vec3 lightDir = normalize(vLight0_Direction.xyz);
	vec3 viewDir = normalize(view - vVertex.xyz);

	//Specular Light Calculations
	vec3 reflected = reflect(-lightDir, viewDir);
	float halfway = dot(reflected, viewDir);
	fSpecularIntensity = max(0.0, dot(normDir, lightDir));
	fSpecularReflection = pow(max(0.0, halfway), 0.5);

	//Diffuse Light
	fDiffuseIntensity = max(0.0, dot(normDir, lightDir));
	
	//Pass UVs to vertex
	fUVcoord = vUV;

	//Convert vertex to world coords
	gl_Position = mvp  * vec4(vVertex, 1.0);
}