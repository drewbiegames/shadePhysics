#include "MovingSphere.h"

#include "Sphere.h"
#include "GLLight.h"
#include "Matrix4D.h"
#include "GLGame.h"
#include "Game.h"

void MovingSphere::Update(){
	
}

void MovingSphere::Draw(){
	if (mShader && mTexture && mMesh){

		glPushMatrix();
		glTranslatef(mTransform.position.X, mTransform.position.Y, mTransform.position.Z);

		GLuint mvp = -1;

		glBindVertexArray(mMesh->getVAO());
		mShader->Enable();

		mvp = mShader->getUniform("mvp");

		TheGLLighting::Instance()->setUniforms(0, *mShader,
			"vLight0_Direction", "fLight0_Ambient",
			"fLight0_Diffuse", "fLight0_Specular");

		GLuint camID = mShader->getUniform("view");
		Vec3* camPos = TheGLGame::Instance()->GetCamera(0)->getPosition();
		glUniform3f(camID, camPos->X, camPos->Y, camPos->Z);

		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		float p[16];
		glGetFloatv(GL_PROJECTION_MATRIX, p);

		Matrix4D mat_m, mat_p;

		mat_m = m;
		mat_p = p;

		Matrix4D mat_mvp = mat_p * mat_m;

		glUniformMatrix4fv(mvp, 1, GL_FALSE, mat_mvp.getMatrix());

		//ActiveTexture: finds the first sampler uniform 
		//and assigns the value to the next glBindTexture call
		glActiveTexture(GL_TEXTURE0);
		mTexture->ApplyTexture();

		mMesh->RenderMeshAtrrib();

		mShader->Disable();

		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();

	}
}

void MovingSphere::Clean(){

}

void MovingSphere::Load(TiXmlElement* node){
	GLGameObject::Load(node);

	mBounds = new Sphere(this, mTransform.position, 
		mRigidBody.getVelocityPtr() , mTransform.rotation, 1.0f);
	TheGame::Instance()->GetCollisionSystem()->RegisterCollidable(this);

	mShader->Enable();

	GLuint vertID	= mShader->getAttribute("vVertex");
	GLuint uvID		= mShader->getAttribute("vUV");
	GLuint normID	= mShader->getAttribute("vNormal");
	mMesh->loadVBOs(vertID, uvID, normID);

	mShader->Disable();

	
}

void MovingSphere::React(GameObject* other){

}

GLfloat MovingSphere::getRadius(){
	Sphere* bound = dynamic_cast<Sphere*>(mBounds);
	GLfloat result = 0.0f;
	if (bound){
		result = bound->Radius;
	}
	return result;
}

static bool sgMovingSphereReg = TheGameObjectFactory::Instance()->RegisterType("Sphere", Create<MovingSphere>);
