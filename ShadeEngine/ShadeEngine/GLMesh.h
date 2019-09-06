#pragma once

#include "Asset.h"

#include <vector>
#include "Vector3D.h"
#include "Vector2D.h"


/*
	OBJ File loader class
	Draws a mesh to the screen
*/

class GLMesh : public Asset {
public:
	bool Load(TiXmlElement* node);

	void RenderMesh();
	void RenderMeshAtrrib();
	
	GLuint getNoVerts(){ return mVertices.size() / 3; }
	
	void loadVBOs(GLuint vert, GLuint uv, GLuint norm);
	void AddData(GLuint vboID, std::vector<GLfloat>& arr, int vertexSize, int attribute);
	
	void EnableAttribute(GLuint atrrib);
	void DisableAttribute(GLuint attrib);

	GLuint getVAO(){ return mVAO; }

	~GLMesh();
private:
	bool loadObj(const std::string& path);

	Vector3Df loadVert(const std::string& substr);
	Vector3Df loadNorm(const std::string& substr);
	Vector2Df loadUV(const std::string& substr);
	void loadFace(const std::string& substr, std::vector<unsigned int>& vertI, std::vector<unsigned int>& uvI, std::vector<unsigned int>& normI, std::vector<unsigned int>& points);

	std::vector<GLfloat> mVertices;
	std::vector<GLfloat> mUVs;
	std::vector<GLfloat> mNormals;

	GLuint mVAO;
	GLuint mVBO_Vertices;
	GLuint mVBO_UVs;
	GLuint mVBO_Normals;
};
