#include "GLGameObject.h"

//Draws TODO: Rewrite Comment
void GLGameObject::Draw(){
	
	if (mShader){
		mShader->Render();
	}
	if (mMaterial) { 
		mMaterial->RenderMaterial();
	}
	if (mTexture)  { 
		mTexture->ApplyTexture(); 
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

//Load from XML Node
void GLGameObject::Load(TiXmlElement* node){
	
	double X, Y, Z;
	
	node->Attribute("posX", &X);
	node->Attribute("posY", &Y);
	node->Attribute("posZ", &Z);

	mTransform.position = Vector3Df(float(X), float(Y), float(Z));

	node->Attribute("rotX", &X);
	node->Attribute("rotY", &Y);
	node->Attribute("rotZ", &Z);

	mTransform.rotation.CreateFromEuler(float(X),float(Y),float(Z));

	std::string matID = node->Attribute("material");
	std::string texID = node->Attribute("texture");
	std::string meshID = node->Attribute("mesh");
	std::string shaderID = node->Attribute("shader");

	mMaterial = TheAssetManager::Instance()->Get<GLMaterial>(matID);
	mTexture = TheAssetManager::Instance()->Get<GLTexture>(texID);
	mMesh = TheAssetManager::Instance()->Get<GLMesh>(meshID);
	mShader = TheAssetManager::Instance()->Get<GLShader>(shaderID);

	for (TiXmlElement* e = node->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == std::string("rigidbody")){
			mRigidBody.Load(node, mTransform);
		}
	}

	/*
		Example XML Base Object Node
		
		<object type="" mesh=""
		 posX="" posY="" posZ=""
		 rotX="" rotY="" rotZ="" rotW=""
		 material="" texture=""
		 shader="" />
	*/
}