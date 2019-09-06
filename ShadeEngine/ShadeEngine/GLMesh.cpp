#include "GLMesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "GLShader.h"
#include "Utils.h"


GLMesh::~GLMesh(){
	glDeleteBuffers(1, &mVBO_Vertices);
	glDeleteBuffers(1, &mVBO_UVs);
	glDeleteBuffers(1, &mVBO_Normals);
}

//Load from XML node
//	Param 1 - XML node
bool GLMesh::Load(TiXmlElement* node){

	std::string path = node->Attribute("path");
	loadObj(path);



	std::string id = node->Attribute("meshid");
	TheAssetManager::Instance()->Add(id, this);

	return true;
}

//Load from file path 
//	Param 1 - file path
bool GLMesh::loadObj(const std::string& path){
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices, nofaceverts;
	std::vector<Vector3Df> verts;
	std::vector<Vector2Df> uvs;
	std::vector<Vector3Df> normals;

	std::ifstream file(path);
	if (!file.is_open()) return false;

	std::string line;
	while (std::getline(file, line)){
		if (line.substr(0, 2) == "v "){
			//vertex
			Vector3Df v = loadVert(line);
			verts.push_back(v);
		}
		else if (line.substr(0, 2) == "vt"){
			//texture coord
			Vector2Df v = loadUV(line);
			uvs.push_back(v);
		}
		else if (line.substr(0, 2) == "vn"){
			//normal
			Vector3Df v = loadNorm(line);
			normals.push_back(v);
		}
		else if (line.substr(0, 2) == "f "){
			//face
			loadFace(line, vertexIndices, uvIndices, normalIndices, nofaceverts);
		}
		else if (line[0] == '#'){}
		else {}
	}


	for (unsigned int ii = 0; ii < vertexIndices.size(); ii++){	
		//Vertex
		mVertices.push_back(verts[vertexIndices[ii]].X);
		mVertices.push_back(verts[vertexIndices[ii]].Y);
		mVertices.push_back(verts[vertexIndices[ii]].Z);

		//UV
		mUVs.push_back(uvs[uvIndices[ii]].X);
		mUVs.push_back(uvs[uvIndices[ii]].Y);

		//Normal
		mNormals.push_back(normals[normalIndices[ii]].X);
		mNormals.push_back(normals[normalIndices[ii]].Y);
		mNormals.push_back(normals[normalIndices[ii]].Z);
	}

	file.close();
	return true;
}

//Creates a vertex from a stirng
Vector3Df GLMesh::loadVert(const std::string& substr){
	std::istringstream str(substr.substr(2));
	std::string x, y, z;
	str >> x;
	str >> y;
	str >> z;
	return Vector3Df(util::toFloat(x), util::toFloat(y), util::toFloat(z));
}

//Creates a normal from a string
Vector3Df GLMesh::loadNorm(const std::string& substr){
	std::istringstream str(substr.substr(2));
	std::string x, y, z;
	str >> x;
	str >> y;
	str >> z;
	return Vector3Df(util::toFloat(x), util::toFloat(y), util::toFloat(z));
}

//Creates a UV from a string
Vector2Df GLMesh::loadUV(const std::string& substr){
	std::istringstream str(substr.substr(2));
	std::string x, y;
	str >> x;
	str >> y;
	//y is fliped in openGL
	return Vector2Df(util::toFloat(x), -util::toFloat(y));
}

//Creates a face
// Param 1 - string that represents the face
// Param 2 - the vector holding the vertex data
// Param 3 - the vector holding the normal data
// Param 4 - the vector holding the uv coord data
void GLMesh::loadFace(const std::string& substr, std::vector<unsigned int>& vertI, std::vector<unsigned int>& uvI, std::vector<unsigned int>& normI, std::vector<unsigned int>& points){
	std::istringstream str(substr.substr(2));
	//account for case of non-grouped faces.
	if (!util::contains(str, '/')){
		std::string i, j, k, l;
		str >> i;
		str >> j;
		str >> k;
		if (str.good())	str >> l;
		return;
	}

	unsigned int noOfVerts = 0;
	while (str.good()){
		//face with groups
		std::string group;
		str >> group;
		std::replace(group.begin(), group.end(), '/', ' ');

		std::istringstream str2(group.substr(0));

		std::string v, uv, n;
		str2 >> v;
		str2 >> uv;
		str2 >> n;

		vertI.push_back(util::toUInt(v) - 1);
		uvI.push_back(util::toUInt(uv) - 1);
		normI.push_back(util::toUInt(n) - 1);
		noOfVerts++;
	}
	points.push_back(noOfVerts);
}


//render the mesh using OpenGL
void GLMesh::RenderMesh(){
	glBegin(GL_TRIANGLES);
	unsigned int uv = 0;
		for (unsigned int ii = 0; ii < mVertices.size(); ii += 3){
			glNormal3f(
				mNormals[ii],
				mNormals[ii+1],
				mNormals[ii+2]);
			glTexCoord2f(
				mUVs[uv],
				mUVs[uv+1]);
			uv += 2;
			glVertex3f(
				mVertices[ii],
				mVertices[ii+1],
				mVertices[ii+2]);
		}
	glEnd();
}

//Test function to render the mesh using shaders
void GLMesh::RenderMeshAtrrib(){
	glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLES, 0, mVertices.size() / 3);
	glBindVertexArray(0);
}

void GLMesh::loadVBOs(GLuint vert, GLuint uv, GLuint norm){
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO_Vertices);
	glGenBuffers(1, &mVBO_UVs);
	glGenBuffers(1, &mVBO_Normals);

	glBindVertexArray(mVAO);

		AddData(mVBO_Vertices, mVertices, 3, vert);
		AddData(mVBO_UVs, mUVs, 2, uv);
		AddData(mVBO_Normals, mNormals, 3, norm);

	glBindVertexArray(0);
}

void GLMesh::AddData(GLuint vboID, std::vector<GLfloat>& arr, int vertexSize, int attribute){
	EnableAttribute(attribute);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	//fill the buffer with data
	glBufferData(GL_ARRAY_BUFFER, sizeof(arr[0]) * arr.size(), &arr[0], GL_DYNAMIC_DRAW);
	//link shader attribute to vertex
	glVertexAttribPointer(attribute, vertexSize, GL_FLOAT, GL_FALSE, 0, 0);
}

void GLMesh::EnableAttribute(GLuint attrib){
	glEnableVertexAttribArray(attrib);
}

void GLMesh::DisableAttribute(GLuint attrib){
	glDisableVertexAttribArray(attrib);
}

static bool sgMeshReg = TheAssetFactory::Instance()->RegisterType("Mesh", Create<GLMesh>);