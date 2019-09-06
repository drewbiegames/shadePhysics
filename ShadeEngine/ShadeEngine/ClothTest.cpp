#include "ClothTest.h"

#include "Matrix4D.h"
#include "GLLight.h"
#include "GLGame.h"
#include "AABB.h"
#include "Utils.h"
#include "MovingSphere.h"
#include "Game.h"

void ClothTest::Update(){
	GLuint width = mParticles.size(), 
		height = mParticles[0].size();

	AddWindForce(mWind);

	for (GLuint ww = 0; ww < width; ++ww){
		for (GLuint hh = 0; hh < height; ++hh){
			//Structural springs
			if (ww != width - 1)
				mParticles[ww][hh]->ClothSpringTo(mParticles[ww + 1][hh], mSeperationStruct, mForceScalarStruct);

			if (hh != height - 1)
				mParticles[ww][hh]->ClothSpringTo(mParticles[ww][hh + 1], mSeperationStruct, mForceScalarStruct);

			//Shear springs
			if (hh != height - 1){
				if (ww != 0)
					mParticles[ww][hh]->ClothSpringTo(mParticles[ww - 1][hh + 1], mSeperationShear, mForceScalarShear);
				if (ww != width - 1)
					mParticles[ww][hh]->ClothSpringTo(mParticles[ww + 1][hh + 1], mSeperationShear, mForceScalarShear);
			}

			//Bend Springs
			if (hh > 2)
				mParticles[ww][hh]->ClothSpringTo(mParticles[ww][hh - 2], mSeperationBend, mForceScalarBend);
			if (hh < height - 3)
				mParticles[ww][hh]->ClothSpringTo(mParticles[ww][hh + 2], mSeperationBend, mForceScalarBend);
			if (ww > 2)
				mParticles[ww][hh]->ClothSpringTo(mParticles[ww - 2][hh], mSeperationBend, mForceScalarBend);
			if (ww < width - 3)
				mParticles[ww][hh]->ClothSpringTo(mParticles[ww + 2][hh], mSeperationBend, mForceScalarBend);

		}
	}

	for (GLuint ww = 0; ww < width; ++ww){
		for (GLuint hh = 0; hh < height; ++hh){
			mParticles[ww][hh]->Update();
		}
	}

	calcAABB();
}

void ClothTest::Draw(){
	//calculate the vertices and normals
	updateVAO();


	glPushMatrix();
		glTranslatef(mTransform.position.X, mTransform.position.Y, mTransform.position.Z);


		glBindVertexArray(mVAO);
		mShader->Enable();

		//Pass light variables to the shader
		TheGLLighting::Instance()->setUniforms(0, *mShader,
			"vLight0_Direction", "fLight0_Ambient",
			"fLight0_Diffuse", "fLight0_Specular");

		//Pass camera to the shader
		GLuint camID = mShader->getUniform("view");
		Vec3* camPos = TheGLGame::Instance()->GetCamera(0)->getPosition();
		glUniform3f(camID, camPos->X, camPos->Y, camPos->Z);
		
		//Calculate the modelviewprojection matrix;
		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		float p[16];
		glGetFloatv(GL_PROJECTION_MATRIX, p);
		Matrix4D mat_m, mat_p;
		mat_m = m;
		mat_p = p;
		Matrix4D mat_mvp = mat_p * mat_m;

		//Pass MVP_Matrix to the shader
		GLuint mvp = mShader->getUniform("mvp");
		glUniformMatrix4fv(mvp, 1, GL_FALSE, mat_mvp.getMatrix());

		//Pass Texture to shader
		glActiveTexture(GL_TEXTURE0);
		mTexture->ApplyTexture();

		//Draw
		glDrawArrays(GL_TRIANGLES, 0, mVertices.size() / 3);

		glBindTexture(GL_TEXTURE_2D, 0);

		mShader->Disable();
		glBindVertexArray(0); 

	glPopMatrix();
}

void ClothTest::Clean(){
	for (unsigned int ii = 0; ii < mParticles.size(); ii++){
		for (unsigned int jj = 0; jj < mParticles[ii].size(); jj++){
			delete mParticles[ii][jj];
			mParticles[ii][jj] = nullptr;
		}
		mParticles[ii].clear();
	}
	mParticles.clear();

}

void ClothTest::Load(TiXmlElement* node){
	GLGameObject::Load(node);

	int width, height;
	node->Attribute("width", &width);
	node->Attribute("height", &height);

	double sep, scale;
	node->Attribute("seperation_struct", &sep);
	node->Attribute("strength_struct", &scale);
	mSeperationStruct = float(sep);
	mForceScalarStruct = float(scale);

	node->Attribute("seperation_shear", &sep);
	node->Attribute("strength_shear", &scale);
	mSeperationShear = float(sep);
	mForceScalarShear = float(scale);

	node->Attribute("seperation_bend", &sep);
	node->Attribute("strength_bend", &scale);
	mSeperationBend = float(sep);
	mForceScalarBend = float(scale);

	double x, y, z;
	node->Attribute("windX", &x);
	node->Attribute("windY", &y);
	node->Attribute("windZ", &z);
	mWind = Vec3(float(x), float(y), float(z));

	for (GLuint ww = 0; ww < GLuint(width); ++ww){
		std::vector<Particle*> vector;
		mParticles.push_back(vector);
		std::vector<Vec3> normals;
		mAccumulatedNormals.push_back(normals);
		for (GLuint hh = 0; hh < GLuint(height); ++hh){
			Vec3 pos, vel;
			pos = Vec3(float((width * sep / 2) - ww * sep), float((height * sep) - (hh * sep)), 0.0f);
			vel = Vec3(0.0f, 0.0f, 0.0f);
			bool fixed = false;
			if ((ww == 0 || ww == width - 1) && hh == 0)
				fixed = true;

			Particle* p = new Particle(pos, vel, 1.0f, 0.99f, fixed, true);
			mParticles[ww].push_back(p);

			Vec3 norm;
			mAccumulatedNormals[ww].push_back(norm);
		}
	}

	makeVAO();
	calcAABB();
}

void ClothTest::React(GameObject* other){
	//not yet implemented
	if (MovingSphere* sphere = dynamic_cast<MovingSphere*>(other)){
		Vec3 pos = *sphere->getPosition();
		GLfloat radius = sphere->getRadius();

		sphereCollisionReaction(pos, radius);
	}
}

void ClothTest::AddWindForce(Vec3 direction){
	//ref: http://cg.alexandra.dk/?p=147
	GLuint width = mParticles.size(),
		height = mParticles[0].size();

	for (GLuint ww = 0; ww < width - 1; ++ww){
		for (GLuint hh = 0; hh < height - 1; ++hh){
			triangleWindForce(mParticles[ww + 1][hh], mParticles[ww][hh], mParticles[ww][hh + 1], direction);
			triangleWindForce(mParticles[ww + 1][hh + 1], mParticles[ww + 1][hh], mParticles[ww][hh + 1], direction);
		}
	}
}

void ClothTest::triangleWindForce(Particle* p1, Particle* p2, Particle* p3, Vec3 direction){
	Vec3 norm = calculateTriangleNormal(p1, p2, p3);
	Vec3 n = norm.normalised();
	Vec3 force = norm * n.dot(direction);
	p1->AddForce(force);
	p2->AddForce(force);
	p3->AddForce(force);
}

Vec3 ClothTest::calculateTriangleNormal(Particle* p1, Particle* p2, Particle* p3){
	Vec3 pos1 = *p1->getPosition();
	Vec3 pos2 = *p2->getPosition();
	Vec3 pos3 = *p3->getPosition();

	Vec3 v1 = pos2 - pos1;
	Vec3 v2 = pos3 - pos1;

	return v1.cross(v2);
}

void ClothTest::createArrays(){
	GLfloat uv_width = 1.0f / (mParticles.size() - 1);
	GLfloat uv_height = 1.0f / (mParticles[0].size() - 1);

	GLuint width = mParticles.size();

	//Vertices
	for (GLuint ww = 0; ww < width; ww++){
		GLuint height = mParticles[ww].size();
		for (GLuint hh = 0; hh < height; hh++){
			Vec3 vert1, vert2, vert3, vert4, norm1, norm2, norm3, norm4;
			if (ww < width - 1 && hh < height - 1){
				
				//Front
				//First Triangle Vertices
				vert1 = *mParticles[ww][hh]->getPosition();
				norm1 = calcNormal(ww, hh, width, height);
				vert2 = *mParticles[ww + 1][hh]->getPosition();
				norm2 = calcNormal(ww + 1, hh, width, height);
				vert3 = *mParticles[ww][hh + 1]->getPosition();
				norm3 = calcNormal(ww, hh + 1, width, height);
				vert4 = *mParticles[ww + 1][hh + 1]->getPosition();
				norm4 = calcNormal(ww + 1, hh + 1, width, height);

				mVertices.push_back(vert1.X);
				mVertices.push_back(vert1.Y);
				mVertices.push_back(vert1.Z);
				mNormals.push_back(norm1.X);
				mNormals.push_back(norm1.Y);
				mNormals.push_back(norm1.Z);
				mUVs.push_back(ww * uv_width);
				mUVs.push_back(hh * uv_height);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm2.X);
				mNormals.push_back(norm2.Y);
				mNormals.push_back(norm2.Z);
				mUVs.push_back((ww + 1) * uv_width);
				mUVs.push_back(hh * uv_height);

				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);
				mUVs.push_back(ww * uv_width);
				mUVs.push_back((hh + 1) * uv_height);

				//Second Traingle Vertices
				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);
				mUVs.push_back(ww * uv_width);
				mUVs.push_back((hh + 1) * uv_height);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);
				mUVs.push_back((ww + 1) * uv_width);
				mUVs.push_back(hh * uv_height);

				mVertices.push_back(vert4.X);
				mVertices.push_back(vert4.Y);
				mVertices.push_back(vert4.Z);
				mNormals.push_back(norm4.X);
				mNormals.push_back(norm4.Y);
				mNormals.push_back(norm4.Z);
				mUVs.push_back((ww + 1) * uv_width);
				mUVs.push_back((hh + 1) * uv_height);

				//Back
				//First Triangle Vertices
				norm1 = -norm1;
				norm2 = -norm2;
				norm3 = -norm3;
				norm4 = -norm4;

				mVertices.push_back(vert1.X);
				mVertices.push_back(vert1.Y);
				mVertices.push_back(vert1.Z);
				mNormals.push_back(norm1.X);
				mNormals.push_back(norm1.Y);
				mNormals.push_back(norm1.Z);
				mUVs.push_back(ww * uv_width);
				mUVs.push_back(hh * uv_height);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm2.X);
				mNormals.push_back(norm2.Y);
				mNormals.push_back(norm2.Z);
				mUVs.push_back((ww + 1) * uv_width);
				mUVs.push_back(hh * uv_height);

				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);
				mUVs.push_back(ww * uv_width);
				mUVs.push_back((hh + 1) * uv_height);

				//Second Traingle Vertices
				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);
				mUVs.push_back(ww * uv_width);
				mUVs.push_back((hh + 1) * uv_height);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);
				mUVs.push_back((ww + 1) * uv_width);
				mUVs.push_back(hh * uv_height);

				mVertices.push_back(vert4.X);
				mVertices.push_back(vert4.Y);
				mVertices.push_back(vert4.Z);
				mNormals.push_back(norm4.X);
				mNormals.push_back(norm4.Y);
				mNormals.push_back(norm4.Z);
				mUVs.push_back((ww + 1) * uv_width);
				mUVs.push_back((hh + 1) * uv_height);

			}
		}
	}
}

void ClothTest::makeVAO(){

	createArrays();
	
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO_vert);
	glGenBuffers(1, &mVBO_uvs);
	glGenBuffers(1, &mVBO_norm);

	mShader->Enable();

	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	float p[16];
	glGetFloatv(GL_PROJECTION_MATRIX, p);

	Matrix4D mat_m, mat_p;

	mat_m = m;
	mat_p = p;

	Matrix4D mat_mvp = mat_p * mat_m;

	glBindVertexArray(mVAO);

	GLuint mvp = mShader->getUniform("mvp");

	glUniformMatrix4fv(mvp, 1, GL_FALSE, mat_mvp.getMatrix());

	GLuint vert_attrib = mShader->getAttribute("vVertex");
	GLuint uv_attrib = mShader->getAttribute("vUV");
	GLuint norm_attrib = mShader->getAttribute("vNormal");

	glEnableVertexAttribArray(vert_attrib);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO_vert);
	//fill the buffer with data
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices[0]) * mVertices.size(), NULL, GL_STREAM_DRAW);
	//link shader attribute to vertex
	glVertexAttribPointer(vert_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(uv_attrib);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO_uvs);
	//fill the buffer with data
	glBufferData(GL_ARRAY_BUFFER, sizeof(mUVs[0]) * mUVs.size(), &mUVs[0], GL_DYNAMIC_DRAW);
	//link shader attribute to vertex
	glVertexAttribPointer(uv_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(norm_attrib);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO_norm);
	//fill the buffer with data
	glBufferData(GL_ARRAY_BUFFER, sizeof(mNormals[0]) * mNormals.size(), NULL, GL_DYNAMIC_DRAW);
	//link shader attribute to vertex
	glVertexAttribPointer(norm_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void ClothTest::updateVAO(){

	mVertices.clear();
	mNormals.clear();

	GLuint width = mParticles.size();
	//Vertices
	for (GLuint ww = 0; ww < width; ww++){
		GLuint height = mParticles[ww].size();
		for (GLuint hh = 0; hh < height; hh++){
			if (ww < width - 1 && hh < height - 1){
				
				Vec3 vert1 = *mParticles[ww][hh]->getPosition();
				Vec3 norm1 = calcNormal(ww, hh, width, height);
				Vec3 vert2 = *mParticles[ww + 1][hh]->getPosition();
				Vec3 norm2 = calcNormal(ww + 1, hh, width, height);
				Vec3 vert3 = *mParticles[ww][hh + 1]->getPosition();
				Vec3 norm3 = calcNormal(ww, hh + 1, width, height);
				Vec3 vert4 = *mParticles[ww + 1][hh + 1]->getPosition();
				Vec3 norm4 = calcNormal(ww + 1, hh + 1, width, height);

				//first triangle
				mVertices.push_back(vert1.X);
				mVertices.push_back(vert1.Y);
				mVertices.push_back(vert1.Z);
				mNormals.push_back(norm1.X);
				mNormals.push_back(norm1.Y);
				mNormals.push_back(norm1.Z);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm2.X);
				mNormals.push_back(norm2.Y);
				mNormals.push_back(norm2.Z);

				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);

				//Second Triangle Vertices
				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);

				mVertices.push_back(vert4.X);
				mVertices.push_back(vert4.Y);
				mVertices.push_back(vert4.Z);
				mNormals.push_back(norm4.X);
				mNormals.push_back(norm4.Y);
				mNormals.push_back(norm4.Z);

				//Back
				//First Triangle Vertices
				norm1 = -norm1;
				norm2 = -norm2;
				norm3 = -norm3;
				norm4 = -norm4;

				mVertices.push_back(vert1.X);
				mVertices.push_back(vert1.Y);
				mVertices.push_back(vert1.Z);
				mNormals.push_back(norm1.X);
				mNormals.push_back(norm1.Y);
				mNormals.push_back(norm1.Z);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm2.X);
				mNormals.push_back(norm2.Y);
				mNormals.push_back(norm2.Z);

				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);

				//Second Triangle Vertices
				mVertices.push_back(vert3.X);
				mVertices.push_back(vert3.Y);
				mVertices.push_back(vert3.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);

				mVertices.push_back(vert2.X);
				mVertices.push_back(vert2.Y);
				mVertices.push_back(vert2.Z);
				mNormals.push_back(norm3.X);
				mNormals.push_back(norm3.Y);
				mNormals.push_back(norm3.Z);

				mVertices.push_back(vert4.X);
				mVertices.push_back(vert4.Y);
				mVertices.push_back(vert4.Z);
				mNormals.push_back(norm4.X);
				mNormals.push_back(norm4.Y);
				mNormals.push_back(norm4.Z);

			}
		}
	}

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_vert);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(mVertices[0]) * mVertices.size(), &mVertices[0]);

	glBindVertexArray(0);


}

Vec3 ClothTest::calcNormal(GLuint ww, GLuint hh, GLuint width, GLuint height){
	Vec3 result = Vec3(0.0f, 0.0f, 0.0f);

	if (ww == 0){
		if (hh == 0){
			//top left corner
			result += calculateTriangleNormal(
				mParticles[ww][hh],
				mParticles[ww + 1][hh],
				mParticles[ww][hh + 1]);
		}
		else if (hh < height - 1){
			//left column (not corner)
			result += calculateTriangleNormal(
				mParticles[ww][hh - 1],
				mParticles[ww + 1][hh],
				mParticles[ww][hh]);
			result += calculateTriangleNormal(
				mParticles[ww][hh],
				mParticles[ww + 1][hh],
				mParticles[ww][hh + 1]);
		}
		else if (hh == height){
			//bottom left corner
			result += calculateTriangleNormal(
				mParticles[ww][hh + 1],
				mParticles[ww + 1][hh],
				mParticles[ww][hh]);
		}
	}
	else if (ww < width - 1){
		if (hh == 0){
			//top row (not corner)
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh],
				mParticles[ww][hh + 1]);
			result += calculateTriangleNormal(
				mParticles[ww][hh],
				mParticles[ww + 1][hh],
				mParticles[ww][hh + 1]);
		}
		else if (hh < height - 1){
			//any middle
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh - 1],
				mParticles[ww][hh]);
			result += calculateTriangleNormal(
				mParticles[ww][hh - 1],
				mParticles[ww + 1][hh],
				mParticles[ww][hh]);
			result += calculateTriangleNormal(
				mParticles[ww + 1][hh],
				mParticles[ww][hh + 1],
				mParticles[ww][hh]);
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh],
				mParticles[ww][hh + 1]);
		}
		else if (hh == height){
			//bottom row (not corner)
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh + 1],
				mParticles[ww][hh]);
			result += calculateTriangleNormal(
				mParticles[ww][hh + 1],
				mParticles[ww + 1][hh],
				mParticles[ww][hh]);
		}
	}
	else if (ww == width){
		if (hh == 0){
			//top right corner
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh],
				mParticles[ww][hh + 1]);
		}
		else if (hh < height - 1){
			//right column (not corner)
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh - 1],
				mParticles[ww][hh]);
			result += calculateTriangleNormal(
				mParticles[ww][hh],
				mParticles[ww][hh + 1],
				mParticles[ww - 1][hh]);
		}
		else if (hh == height){
			//bottom right corner
			result += calculateTriangleNormal(
				mParticles[ww - 1][hh],
				mParticles[ww][hh - 1],
				mParticles[ww][hh]);
		}
	}

	return result;
}

void ClothTest::sphereCollisionReaction(Vec3 centre, GLfloat radius){
	//collision system errors: implementation TODO
	for (GLuint ww = 0; ww < mParticles.size(); ww++){
		for (GLuint hh = 0; hh < mParticles.size(); hh++){
			Vec3 pos = *mParticles[ww][hh]->getPosition() + mTransform.position;
			Vec3 dif = pos - centre;
			GLfloat sqDist = dif.SqLength();
			if (sqDist < radius * radius){
				GLfloat dist = dif.Length();
				dif.normalise();
				*mParticles[ww][hh]->getPosition() += dif * (radius - dist);
			}
		}
	}
}

void ClothTest::calcAABB(){
	AABB* aabb = dynamic_cast<AABB*>(mBounds);

	if (aabb){
		
		Vec3 max, min;

		GLuint width = mParticles.size();
		GLuint height = mParticles[0].size();

		for (GLuint ww = 0; ww < width; ++ww){
			for (GLuint hh = 0; hh < height; ++hh){

				Vec3 pos = mTransform.position + *mParticles[ww][hh]->getPosition();

				if (ww == 0 && hh == 0){
					max = pos;
					min = pos;
				}
				
				max.X = std::max(max.X, pos.X);
				max.Y = std::max(max.Y, pos.Y);
				max.Z = std::max(max.Z, pos.Z);

				min.X = std::min(min.X, pos.X);
				min.Y = std::min(min.Y, pos.Y);
				min.Z = std::min(min.Z, pos.Z);
			}
		}
		aabb->Max = max;
		aabb->Min = min;
	}
}

static bool sgClothTestReg = TheGameObjectFactory::Instance()->RegisterType("Cloth", Create<ClothTest>);