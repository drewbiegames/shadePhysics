#include "GLDebugGrid.h"

#include "Matrix4D.h"


GLDebugGrid::GLDebugGrid() 
	: mHalfedLength(5.0f), mLinesPerAxis(11), mSpaceBetweenLines(1.0f)
{
	Init(mLinesPerAxis);
}

void GLDebugGrid::Update(){

}

void GLDebugGrid::Draw(){
	glPushMatrix();

	mShader->Enable();
	GLuint mvpID = mShader->getUniform("mv");
	GLuint prjID = mShader->getUniform("proj");

	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	float p[16];
	glGetFloatv(GL_PROJECTION_MATRIX, p);

	glUniformMatrix4fv(prjID, 1, GL_FALSE, &p[0]);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &m[0]);
	glBindVertexArray(mVAO);
		glDrawArrays(GL_LINES, 0, mCount);
	glBindVertexArray(0);
	mShader->Disable();

	glPopMatrix();
}

void GLDebugGrid::Clean(){

}

void GLDebugGrid::Load(TiXmlElement* node){

}

void GLDebugGrid::React(GameObject* other){

}

void GLDebugGrid::Init(GLuint size){
	mShader = new GLShader();
	mShader->Load("grid", "Media/Core/grid.vert", "Media/Core/grid.frag");

	GLint halflines = int(size * 0.5f);

	std::vector<GLfloat> verts;
	std::vector<GLfloat> colours;

	for (int zz = -halflines; zz <= halflines; ++zz){
		//vert one - z
		verts.push_back(-mHalfedLength); verts.push_back(0.0f); verts.push_back(zz * mSpaceBetweenLines);
		if (zz == 0) { colours.push_back(0.0f); colours.push_back(0.0f); colours.push_back(1.0f); }
		else { colours.push_back(1.0f); colours.push_back(1.0f); colours.push_back(1.0f); }
		//vert two
		verts.push_back(mHalfedLength); verts.push_back(0.0f); verts.push_back(zz * mSpaceBetweenLines);
		if (zz == 0) { colours.push_back(0.0f); colours.push_back(0.0f); colours.push_back(1.0f); }
		else { colours.push_back(1.0f); colours.push_back(1.0f); colours.push_back(1.0f); }
	}
	for (int xx = -halflines; xx <= halflines; ++xx){
		//vert one - x
		verts.push_back(xx * mSpaceBetweenLines); verts.push_back(0.0f); verts.push_back(-mHalfedLength);
		if (xx == 0) { colours.push_back(1.0f); colours.push_back(0.0f); colours.push_back(0.0f); }
		else { colours.push_back(1.0f); colours.push_back(1.0f); colours.push_back(1.0f); }
		//vert two
		verts.push_back(xx * mSpaceBetweenLines); verts.push_back(0.0f); verts.push_back(mHalfedLength);
		if (xx == 0) { colours.push_back(1.0f); colours.push_back(0.0f); colours.push_back(0.0f); }
		else { colours.push_back(1.0f); colours.push_back(1.0f); colours.push_back(1.0f); }
	}

	mCount = verts.size() / 3;

	//Generate Buffers
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO_verts);
	glGenBuffers(1, &mVBO_color);

	GLuint colorAttrib = mShader->getAttribute("vColour");
	GLuint vertAttrib = mShader->getAttribute("vVert");

	//bind VAO
	glBindVertexArray(mVAO);

		//populate VBO - vertex
		glBindBuffer(GL_ARRAY_BUFFER, mVBO_verts);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0]) * verts.size(), &verts[0], GL_STATIC_DRAW);
		//attribute pointer - vertex
		glEnableVertexAttribArray(vertAttrib);
		glVertexAttribPointer(vertAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		//populate VBO - colour
		glBindBuffer(GL_ARRAY_BUFFER, mVBO_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colours[0]) * verts.size(), &colours[0], GL_STATIC_DRAW);
		//attribute pointer - colour
		glEnableVertexAttribArray(colorAttrib);
		glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//unbind VAO
	glBindVertexArray(0);
}