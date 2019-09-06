#pragma once

#include "Defines.h"
#include "tinyxml.h"
#include "Asset.h"
#include <string>

/*
	GL Shader Manager

	Not complete, needs to store more than one shader

	Loads in shaders from files and stores 
	them on the graphics card
*/


enum ShaderType {
	VERTEX_SHADER, 
	FRAGMENT_SHADER, 
	GEOMETRY_SHADER
};

class GLShader : public Asset {
public:
	GLShader() :
		mProgram(0), mVertexShader(0),
		mFragmentShader(0), mGeometryShader(0)
	{}

	bool Load(TiXmlElement* node);
	bool Load(const std::string& id, const std::string& vertexPath, const std::string& fragPath);
	
	void Enable();
	void Render();
	void Disable();
	void Clean();

	GLuint getUniform(const std::string& name);
	GLuint getAttribute(const std::string& name);

	~GLShader(){ Clean(); }

private:

	bool init();
	bool link();
	bool compile(const std::string& filename, ShaderType shader);

	GLint mProgram;
	GLint mVertexShader;
	GLint mFragmentShader;
	GLint mGeometryShader;
};
