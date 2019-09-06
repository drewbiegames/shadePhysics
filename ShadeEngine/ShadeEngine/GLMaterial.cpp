#include "GLMaterial.h"

#include "Utils.h"

#include <fstream>
#include <sstream>

//Apply material
void GLMaterial::RenderMaterial(){
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);

	glMaterialf(GL_FRONT, GL_SHININESS, mShine);
}

//Load mat from GLfoat[13]
void GLMaterial::Load(GLfloat mat[13]){

	setAmbient(mat[M_AMB_RED], mat[M_AMB_GRN], mat[M_AMB_BLU], mat[M_AMB_ALP]);

	setDiffuse(mat[M_DIF_RED], mat[M_DIF_GRN], mat[M_DIF_BLU], mat[M_DIF_ALP]);

	setSpecular(mat[M_SPC_RED], mat[M_SPC_GRN], mat[M_SPC_BLU], mat[M_SPC_ALP]);

	setShine(mat[M_SHINE]);
}

//Load material from XML Node
bool GLMaterial::Load(TiXmlElement* node){
	
	double ambR, ambG, ambB, ambA,
		difR, difG, difB, difA,
		spcR, spcG, spcB, spcA,
		shine;

	node->Attribute("amb_red", &ambR);
	node->Attribute("amb_green", &ambG);
	node->Attribute("amb_blue", &ambB);
	node->Attribute("amb_alpha", &ambA);

	node->Attribute("dif_red", &difR);
	node->Attribute("dif_green", &difG);
	node->Attribute("dif_blue", &difB);
	node->Attribute("dif_alpha", &difA);

	node->Attribute("spc_red", &spcR);
	node->Attribute("spc_green", &spcG);
	node->Attribute("spc_blue", &spcB);
	node->Attribute("spc_alpha", &spcA);

	node->Attribute("shine", &shine);

	GLfloat mat[13] = {
		float(ambR), float(ambG), float(ambB), float(ambA),
		float(difR), float(difG), float(difB), float(difA),
		float(spcR), float(spcG), float(spcB), float(spcA),
		float(shine * 128)
	};

	Load(mat);

	std::string texID = node->Attribute("materialID");

	TheAssetManager::Instance()->Add(texID, this);

	return true;

	/*
		Example XML Light Node

		<gl_material materialID="none"
		 amb_red="0.2" amb_green="0.2" amb_blue="0.2" amb_alpha="1.0"
		 dif_red="0.8" dif_green="0.8" dif_blue="0.8" dif_alpha="1.0"
		 spc_red="0.0" spc_green="0.0" spc_blue="0.0" spc_alpha="1.0"
		 shine="0.0"/>
	*/
};

//Load from MTL file - not tested
//	Param 1 - path to the MTL file
bool GLMaterial::Load(std::string path){

	std::ifstream file(path);
	if (!file.is_open()) return false;

	float mat[13];

	std::string line;
	std::string var;
	while (std::getline(file, line)){
		if (line.substr(0, 2) == "Ka"){
			//ambient
			std::istringstream str(line.substr(2));
			int ii = 0;
			while (str.good()){
				str >> var;
				mat[ii] = util::toFloat(var);
				ii++;
			}
			mat[3] = 1.0f;
		}
		else if (line.substr(0, 2) == "Kd"){
			//diffuse
			std::istringstream str(line.substr(2));
			int ii = 4;
			while (str.good()){
				str >> var;
				mat[ii] = util::toFloat(var);
				ii++;
			}
			mat[7] = 1.0f;
		}
		else if (line.substr(0, 2) == "Ks"){
			//specular
			std::istringstream str(line.substr(2));
			int ii = 8;
			while (str.good()){
				str >> var;
				mat[ii] = util::toFloat(var);
				ii++;
			}
			mat[11] = 1.0f;
		}
		else if (line.substr(0, 2) == "Ns"){
			//shine
			std::istringstream str(line.substr(2));
			str >> var;
			mat[12] = util::toFloat(var);
		}
		else { /* do nothing */ }
	}

	Load(mat);
	return true;
}

//Set Ambient Values
void GLMaterial::setAmbient(GLfloat R, GLfloat G, GLfloat B, GLfloat A){
	mAmbient[0] = R;
	mAmbient[1] = G;
	mAmbient[2] = B;
	mAmbient[3] = A;

}

//Set Diffuse Values
void GLMaterial::setDiffuse(GLfloat R, GLfloat G, GLfloat B, GLfloat A){
	mDiffuse[0] = R;
	mDiffuse[1] = G;
	mDiffuse[2] = B;
	mDiffuse[3] = A;
}

//Set Specular values
void GLMaterial::setSpecular(GLfloat R, GLfloat G, GLfloat B, GLfloat A){
	mSpecular[0] = R;
	mSpecular[1] = G;
	mSpecular[2] = B;
	mSpecular[3] = A;
}

//Set Shininess
void GLMaterial::setShine(GLfloat shine){
	mShine = shine;
}

//Set Shininess
//	Param 1 - Material Enum of value to change
//	Param 2 - Value to change to
void GLMaterial::set(Mat prop, GLfloat value){
	if (util::InRange(prop, M_AMB_RED, M_AMB_ALP)){
		mAmbient[prop] = value;
	}
	else if (util::InRange(prop, M_DIF_RED, M_DIF_ALP)){
		mDiffuse[prop - 4] = value;
	}
	else if (util::InRange(prop, M_SPC_RED, M_DIF_ALP)){
		mSpecular[prop - 8] = value;
	}
	else if (prop == M_SHINE){
		mShine = value;
	}
}

static bool sgMaterialRegister = TheAssetFactory::Instance()->RegisterType("GLMaterial", Create<GLMaterial>);