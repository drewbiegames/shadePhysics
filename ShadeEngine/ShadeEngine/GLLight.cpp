#include "GLLight.h"

#include "Defines.h"

#include "Utils.h"

//Load from XML Node
void GLLight::Load(TiXmlElement* node){
	int lightID;

	node->Attribute("light", &lightID);

	Light temp;

	double x, y, z, w;

	node->Attribute("posX", &x);
	node->Attribute("posY", &y);
	node->Attribute("posZ", &z);
	node->Attribute("posW", &w);

	temp.direction.X = float(x);
	temp.direction.Y = float(y);
	temp.direction.Z = float(z);
	temp.direction.W = float(w);

	double r, g, b, a;

	node->Attribute("amb_red",   &r);
	node->Attribute("amb_green", &g);
	node->Attribute("amb_blue",  &b);
	node->Attribute("amb_alpha", &a);

	Colour amb(r, g, b, a);
	temp.ambient = amb;

	node->Attribute("dif_red", &r);
	node->Attribute("dif_green", &g);
	node->Attribute("dif_blue", &b);
	node->Attribute("dif_alpha", &a);

	Colour dif(r, g, b, a);
	temp.diffuse = dif;

	node->Attribute("spc_red", &r);
	node->Attribute("spc_green", &g);
	node->Attribute("spc_blue", &b);
	node->Attribute("spc_alpha", &a);

	Colour spec(r, g, b, a);
	temp.specular = spec;

	mLightMap.push_back(temp);


	/*
		Example Light Node

		<object type="Light" light="1"
          posX="2.0" posY="5.0" posZ="3.0" posW="0.0"
          amb_red="0.3" amb_green="0.3" amb_blue="0.3" amb_alpha="1.0"
          dif_red="0.4" dif_green="0.4" dif_blue="0.4" dif_alpha="1.0"
          spc_red="1.0" spc_green="1.0" spc_blue="1.0" spc_alpha="1.0"
		  shine="1.0"
          />
	*/

}

void GLLight::setUniforms(GLuint lightID,
	GLShader& shader,
	const std::string& uniformDir,
	const std::string& uniformAmb,
	const std::string& uniformDif,
	const std::string& uniformSpec)
{
	if (lightID > mLightMap.size() - 1) return;

	GLuint dir, amb, dif, spec;

	dir = shader.getUniform(uniformDir);
	GLfloat dirVec[4] = {
		mLightMap[lightID].direction.X,
		mLightMap[lightID].direction.Y,
		mLightMap[lightID].direction.Z,
		mLightMap[lightID].direction.W 
	};
	glUniform4f(dir, dirVec[0], dirVec[1], dirVec[2], dirVec[3]);
	
	amb = shader.getUniform(uniformAmb);
	GLfloat ambVec[4] = {
		mLightMap[lightID].ambient.A,
		mLightMap[lightID].ambient.G,
		mLightMap[lightID].ambient.B,
		mLightMap[lightID].ambient.A
	};
	glUniform4f(amb, ambVec[0], ambVec[1], ambVec[2], ambVec[3]);

	dif = shader.getUniform(uniformDif);
	GLfloat difVec[4] = {
		mLightMap[lightID].diffuse.A,
		mLightMap[lightID].diffuse.G,
		mLightMap[lightID].diffuse.B,
		mLightMap[lightID].diffuse.A
	};
	glUniform4f(dif, difVec[0], difVec[1], difVec[2], difVec[3]);

	spec = shader.getUniform(uniformSpec);
	GLfloat specVec[4] = {
		mLightMap[lightID].specular.A,
		mLightMap[lightID].specular.G,
		mLightMap[lightID].specular.B,
		mLightMap[lightID].specular.A
	};
	glUniform4f(spec, specVec[0], specVec[1], specVec[2], specVec[3]);
}

void GLLight::setPosition(GLuint lightID, GLfloat xpos, GLfloat ypos, GLfloat zpos, GLfloat wpos){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].direction.X = xpos;
	mLightMap[lightID].direction.Y = ypos;
	mLightMap[lightID].direction.Z = zpos;
	mLightMap[lightID].direction.W = wpos;
}

void GLLight::setAmbient(GLuint lightID, GLfloat ambR, GLfloat ambG, GLfloat ambB, GLfloat ambA){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].ambient.R = ambR;
	mLightMap[lightID].ambient.G = ambG;
	mLightMap[lightID].ambient.B = ambB;
	mLightMap[lightID].ambient.A = ambA;
}

void GLLight::setDiffuse(GLuint lightID, GLfloat difR, GLfloat difG, GLfloat difB, GLfloat difA){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].diffuse.R = difR;
	mLightMap[lightID].diffuse.G = difG;
	mLightMap[lightID].diffuse.B = difB;
	mLightMap[lightID].diffuse.A = difA;
}

void GLLight::setSpecular(GLuint lightID, GLfloat ambR, GLfloat ambG, GLfloat ambB, GLfloat ambA){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].ambient.R = ambR;
	mLightMap[lightID].ambient.G = ambG;
	mLightMap[lightID].ambient.B = ambB;
	mLightMap[lightID].ambient.A = ambA;
}

void GLLight::setPosition(GLuint lightID, Vector4Df dir){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].direction = dir;
}

void GLLight::setAmbient(GLuint lightID, Colour amb){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].ambient = amb;
}

void GLLight::setDiffuse(GLuint lightID, Colour dif){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].diffuse = dif;
}

void GLLight::setSpecular(GLuint lightID, Colour spec){
	if (lightID > mLightMap.size() - 1) return;

	mLightMap[lightID].specular = spec;
}