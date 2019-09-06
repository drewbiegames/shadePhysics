#pragma once

#include <vector>

#include "Colour.h"
#include "Vector4D.h"
#include "Singleton.h"
#include "GLShader.h"

enum LightEnum {
	L_POS_X,   L_POS_Y,   L_POS_Z,   L_POS_DIR,
	L_AMB_RED, L_AMB_GRN, L_AMB_BLU, L_AMB_ALP,
	L_DIF_RED, L_DIF_GRN, L_DIF_BLU, L_DIF_ALP,
	L_SPC_RED, L_SPC_GRN, L_SPC_BLU, L_SPC_ALP,
};

struct Light {
	Vector4Df direction;
	Colour ambient;
	Colour diffuse;
	Colour specular;
};

class GLLight : public Uncopyable {
public:
	void Load(TiXmlElement* node);

	void setUniforms(GLuint lightID, 
		GLShader& shader, 
		const std::string& uniformDir, 
		const std::string& uniformAmb, 
		const std::string& uniformDif, 
		const std::string& uniformSpec);

	void setPosition(GLuint lightID, GLfloat xpos, GLfloat ypos, GLfloat zpos, GLfloat wpos);
	void setAmbient (GLuint lightID, GLfloat ambR, GLfloat ambG, GLfloat ambB, GLfloat ambA);
	void setDiffuse (GLuint lightID, GLfloat difR, GLfloat difG, GLfloat difB, GLfloat difA);
	void setSpecular(GLuint lightID, GLfloat ambR, GLfloat ambG, GLfloat ambB, GLfloat ambA);

	void setPosition(GLuint lightID, Vector4Df dir);
	void setAmbient(GLuint lightID, Colour amb);
	void setDiffuse(GLuint lightID, Colour dif);
	void setSpecular(GLuint lightID, Colour spec);

private:
	friend class SingletonT < GLLight > ;
	GLLight(){}

	typedef std::vector<Light> LightContainer;

	LightContainer mLightMap;
};

typedef SingletonT<GLLight> TheGLLighting;