#include "Cube.h"

#include "Utils.h"

//Updates Cube
void Cube::Update(){
	
}

//Draws Cube
//	If a texture is present uses vertex drawn cube
//	Otherwise draws glutSolidCube() when material present
void Cube::Draw(){
	

	//glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
		GLGameObject::Draw();
		if (mTexture){
			util::GLTexturedCube(mSize);
		}
		else if (mMaterial){
			glutSolidCube(mSize);
		}
		else{
			throw("Cube not drawn!");
			assert(false);
		}

	glPopMatrix();

}

void Cube::Clean(){
	
}

//Load from XML node
//	Param 1 - XML Node
void Cube::Load(TiXmlElement* node){
	GLGameObject::Load(node);

	double size;
	node->Attribute("size", &size);

	mSize = float(size);

	/* Example XML node
	
	 <object type="Cube" size="1.0"
      posX="0" posY="0" posZ="0"
      rotX="1" rotY="1" rotZ="1" rotW="90"
      material="gold" texture="none"
      />

	*/
}

void Cube::Load(Vector3Df pos){
	
}

static bool sgCubeRegister = TheGameObjectFactory::Instance()->RegisterType("Cube", Create<Cube>);