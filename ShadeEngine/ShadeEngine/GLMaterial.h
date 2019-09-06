#pragma once

#include "Asset.h"

#include "Defines.h"
#include "tinyxml.h"

/*
	GLMaterial Enum

	Used to access the correct part of the array when 
	setting and getting values from the material
*/

enum Mat {
	M_AMB_RED, M_AMB_GRN, M_AMB_BLU, M_AMB_ALP,
	M_DIF_RED, M_DIF_GRN, M_DIF_BLU, M_DIF_ALP,
	M_SPC_RED, M_SPC_GRN, M_SPC_BLU, M_SPC_ALP,
	M_SHINE
};

class GLMaterial : public Asset {
public:
	GLMaterial(){};

	~GLMaterial(){};

	void RenderMaterial();

	void setAmbient(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	void setDiffuse(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	void setSpecular(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	void setShine(GLfloat shine);

	bool Load(TiXmlElement* node);
	void Load(GLfloat mat[13]);
	bool Load(std::string path);

	//Set the corrosponding value to the enum passed
	void set(Mat prop, GLfloat value);

private:
	GLfloat mAmbient[4];
	GLfloat mDiffuse[4];
	GLfloat mSpecular[4];
	GLfloat mShine;
};