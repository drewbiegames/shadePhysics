#include "GLGameObject.h"

/*
	Texture Quad class

	draws a square with a texture
*/

class TextureQuad : public GLGameObject {
public:
	
	void Update();
	void Draw();
	void Clean();
	void React(GameObject* obj){}

	void Load(TiXmlElement*);

	~TextureQuad(){ Clean(); }

private:
	//Fragment Uniform Variables
	GLfloat fMaxTime;
	GLfloat fTime;
	GLfloat fBurnStep;
};