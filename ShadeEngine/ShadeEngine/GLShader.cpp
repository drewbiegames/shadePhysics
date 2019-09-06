#include "GLShader.h"

#include <fstream>
#include <iostream>

GLuint GLShader::getUniform(const std::string& name){
	return glGetUniformLocation(mProgram, name.c_str());
}

GLuint GLShader::getAttribute(const std::string& name){
	GLuint i = glGetAttribLocation(mProgram, name.c_str());

	return glGetAttribLocation(mProgram, name.c_str());
}

bool GLShader::init(){

	//create shader program
	mProgram = glCreateProgram();

	//error check program
	if (mProgram == -1){
		printf("Shader program could not be created.\n");
		return false;
	}

	//create vertex shader
	mVertexShader = glCreateShader(GL_VERTEX_SHADER);

	//error check vertex shader
	if (mVertexShader == -1){
		printf("Vertex Shader could not be created.\n");
		return false;
	}

	//attach shader to main program
	glAttachShader(mProgram, mVertexShader);

	//create fragment shader
	mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//error check vertex shader
	if (mFragmentShader == -1){
		printf("Fragment Shader could not be created.\n");
		return false;
	}

	//attach shader to program
	glAttachShader(mProgram, mFragmentShader);
	return true;
}

bool GLShader::compile(const std::string& filename, ShaderType shader){
	std::fstream file;
	std::string linetext = "";
	std::string finalstring;
	GLint tempShader;
	GLint compileResult;

	file.open(filename);

	//file error check
	if (!file){
		printf("Shader file %s could not be loaded.\n", filename.c_str());
		return false;
	}

	//assign correct ID to temp shader
	if (shader == VERTEX_SHADER){ tempShader = mVertexShader; }
	else if (shader == FRAGMENT_SHADER) { tempShader = mFragmentShader; }
	else if (shader == GEOMETRY_SHADER) { tempShader = mGeometryShader; }

	//read the file and store in final string
	while (!file.eof()){
		std::getline(file, linetext);
		finalstring += linetext + "\n";
	}
	file.close();

	const GLchar* finalCode = static_cast<const GLchar*>(finalstring.c_str());

	//debug output
	//printf("---------------------------------------------------------------\n");
	//printf("Compiling %s Shader...\n", (shader == VERTEX_SHADER ? "Vertex" : "Fragment"));
	//printf("---------------------------------------------------------------\n");


	//bind shader object with the shader source code
	glShaderSource(tempShader, 1, &finalCode, NULL);
	
	//complie shader
	glCompileShader(tempShader);

	glGetShaderiv(tempShader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_TRUE){	}
	else{
		GLchar error[1000];

		printf("---------------------------------------------------------------\n");
		printf("Compilation: Failure\n");
		printf("---------------------------------------------------------------\n");
		
		std::cout << finalstring << std::endl;

		glGetShaderInfoLog(tempShader, 1000, NULL, error);
		printf("%s\n", static_cast<const std::string>(error).c_str());
		printf("---------------------------------------------------------------\n");

		return false;
	}

	return true;
}

bool GLShader::link(){
	GLint linkResult;

	//link the entire shader program
	glLinkProgram(mProgram);

	//error checking
	glGetProgramiv(mProgram, GL_LINK_STATUS, &linkResult);

	//success
	if (linkResult == GL_TRUE){
		//printf("Linking: Success\n");
		//printf("Shader program created.\n");
	}
	//failure
	else{
		GLchar error[1000];
		GLsizei length = 1000;

		printf("---------------------------------------------------------------\n");
		printf("Linking: Failure\n");
		printf("---------------------------------------------------------------\n");

		glGetShaderInfoLog(mProgram, 1000, &length, error);
		printf("%s\n", static_cast<const std::string>(error).c_str());
		printf("---------------------------------------------------------------\n");

		return false;
	}

	return true;
}

//Use this shader
void GLShader::Enable(){
	glUseProgram(mProgram);
	//printf("Shader program enabled.\n");
}

//Call to use the shader each frame
void GLShader::Render(){
	//float proj[16];
	//glGetFloatv(GL_PROJECTION_MATRIX, proj);
	//
	//float modelveiw[16];
	//glGetFloatv(GL_MODELVIEW_MATRIX, modelveiw);
	//
	//GLint projUni = getUniform("projectionMatrix");
	//GLint modelveiwUni = getUniform("modelviewMatrix");
	//
	//glUniformMatrix4fv(projUni, 1, GL_FALSE, proj);
	//glUniformMatrix4fv(modelveiwUni, 1, GL_FALSE, modelveiw);
}

//deactivate shader
//uses default shader
void GLShader::Disable(){
	glUseProgram(0);
	//printf("Using Default Shader.\n");
}

//detaches and destroys shaders from the program
void GLShader::Clean(){
	glDetachShader(mProgram, mFragmentShader);
	glDetachShader(mProgram, mVertexShader);

	glDeleteShader(mFragmentShader);
	glDeleteShader(mVertexShader);

	glDeleteProgram(mProgram);

	mProgram = mVertexShader = mFragmentShader = mGeometryShader = 0;
}

bool GLShader::Load(TiXmlElement* node){
	if (!init()){ 
		return false; 
	}

	std::string vertexpath = node->Attribute("vertexpath");
	std::string fragmentpath = node->Attribute("fragmentpath");
	std::string id = node->Attribute("id");

	compile(vertexpath, VERTEX_SHADER);
	compile(fragmentpath, FRAGMENT_SHADER);

	if (!link()){ 
		//TODO: Input Error
		return false; 
	}

	TheAssetManager::Instance()->Add(id, this);

	return true;
}

bool GLShader::Load(const std::string& id, const std::string& vertexPath, const std::string& fragPath){
	if (!init()){
		return false;
	}

	compile(vertexPath, VERTEX_SHADER);
	compile(fragPath, FRAGMENT_SHADER);

	if (!link()){
		//TODO: Input Error
		return false;
	}

	//TheAssetManager::Instance()->Add(id, this);

	return true;
}

static bool sgGLShaderReg = TheAssetFactory::Instance()->RegisterType("GLShader", Create<GLShader>);