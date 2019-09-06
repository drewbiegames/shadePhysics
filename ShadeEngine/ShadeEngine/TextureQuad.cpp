#include "TextureQuad.h"

#include "Utils.h"
#include "Matrix4D.h"
#include "GLGame.h"
#include "GLLight.h"
#include "Timer.h"

void TextureQuad::Update(){

}

//Draws a plane with a texture
void TextureQuad::Draw(){
	glPushMatrix();

	float angle = util::DegreesFromRadians(acosf(mTransform.rotation.W)) * 2;
	Vec3 axis = Vec3(mTransform.rotation.X, mTransform.rotation.Y, mTransform.rotation.Z);
	glTranslatef(mTransform.position.X, mTransform.position.Y, mTransform.position.Z);
	glRotatef(angle, axis.X, axis.Y, axis.Z);

	mShader->Enable();
	glBindVertexArray(mMesh->getVAO());

	//Sending Animation Values to shader
	fTime += TheTimer::Instance()->GetDeltaTime();
	util::wrapValue(fTime, 0.0f, fMaxTime);
	GLuint timeID = mShader->getUniform("fTime");
	GLuint maxTimeID = mShader->getUniform("fMaxTime");
	GLuint burnstepID = mShader->getUniform("fBurnStep");
	glUniform1f(timeID, fTime);
	glUniform1f(maxTimeID, fMaxTime);
	glUniform1f(burnstepID, fBurnStep);

	//Send lighting variables to shader
	TheGLLighting::Instance()->setUniforms(0, *mShader,
		"vLight0_Direction", "fLight0_Ambient",
		"fLight0_Diffuse", "fLight0_Specular");

	//Send texture to shader
	if (mTexture){
		glActiveTexture(GL_TEXTURE0);
		mTexture->ApplyTexture();
		glUniform1i(mShader->getUniform("fMainTexture"), 0);
	}

	//Send modelviewprojection matrix to shader
	float mv[16];
	float p[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mv);
	glGetFloatv(GL_PROJECTION_MATRIX, p);
	Matrix4D mat_mv, mat_p;
	mat_mv = mv;
	mat_p = p;
	Matrix4D mat_mvp = mat_p * mat_mv;
	GLuint mvp = mShader->getUniform("mvp");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, mat_mvp.getMatrix());

	//Send camera position to the shader
	GLuint camID = mShader->getUniform("view");
	Vec3* camPos = TheGLGame::Instance()->GetCamera(0)->getPosition();
	glUniform3f(camID, camPos->X, camPos->Y, camPos->Z);

	//Draw the mesh
 	mMesh->RenderMeshAtrrib();
	
	glPopMatrix();

	glBindVertexArray(0);
	mShader->Disable();
}

void TextureQuad::Clean(){
	
}

//Load from XML Node
void TextureQuad::Load(TiXmlElement* node){
	GLGameObject::Load(node);

	double maxtime, burnstep;
	node->Attribute("MaxTime", &maxtime);
	node->Attribute("BurnStep", &burnstep);

	fMaxTime = GLfloat(maxtime);
	fTime = 0.0f;
	fBurnStep = GLfloat(burnstep);

	//load the VBOs
	GLuint vertID = mShader->getAttribute("vVertex");
	GLuint uvID = mShader->getAttribute("vUV");
	GLuint normID = mShader->getAttribute("vNormal");
	mMesh->loadVBOs(vertID, uvID, normID);
}

static bool sgTextureQuadReg = TheGameObjectFactory::Instance()->RegisterType("TextureQuad", Create<TextureQuad>);