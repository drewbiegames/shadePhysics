#include "TextBox.h"

//Draw the text to screen
void TextBox::Draw(){
	mTextureP->Draw(int(mPosition.X), int(mPosition.Y), mWidth, mHeight);
}

//Clean object pointers
void TextBox::Clean(){
	delete mTextureP;
	mTextureP = nullptr;
}

//Load from XML node
//	Param 1 - XML object node
void TextBox::Load(TiXmlElement* node){
	mTextureP = new Text();
	mTextureP->Load(node);
	mText = node->Attribute("text");
	int x, y;
	node->Attribute("x", &x);
	node->Attribute("y", &y);

	mPosition = Vector2Df(float(x), float(y));
	mWidth = mTextureP->getWidth();
	mHeight = mTextureP->getHeight();

}

//Assignment operator overload to set the text.
//	Param 1 - string to change to
void TextBox::operator=(const std::string& newText){
	if (mText != newText){
		mTextureP->ChangeText(newText);
		mText = newText;
	}
}

static bool sgTextBoxRegister = TheGameObjectFactory::Instance()->RegisterType("TextBox", Create<TextBox>);