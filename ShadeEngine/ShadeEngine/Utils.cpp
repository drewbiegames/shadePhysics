#include "Utils.h"

#include "Defines.h"

float util::DegreesFromRadians(float radians){
	return float((radians / M_PI) * 180);
}

float util::RadiansFromDegrees(float degrees){
	return float((degrees / 180) * M_PI);
}

void util::GLRenderVec3(Vector3Df vec, Vector3Df origin, Vector3Df colour){
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
		glBegin(GL_LINES);
			glColor3f(colour.X, colour.Y, colour.Z);
			glVertex3f(origin.X, origin.Y, origin.Z);
			glVertex3f(vec.X, vec.Y, vec.Z);
		glEnd();

		//glColor3f(1.0, 0.0, 0.0);
		glTranslatef(vec.X, vec.Y, vec.Z);
		glutSolidSphere(0.1, 4, 4);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void util::GLTexturedCube(GLfloat size){

	//ref: http://nehe.gamedev.net/tutorial/texture_mapping/12038/
	//for drawing a cube, which had flipped textures, corrected by me

	float p = 0.5f * size;
	
	glPushMatrix();

		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-p, -p, p);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(p, -p, p);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(p, p, p);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, p, p);  // Top Left Of The Texture and Quad
			// Back Face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-p, -p, -p);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-p, p, -p);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(p, p, -p);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(p, -p, -p);  // Bottom Left Of The Texture and Quad
			// Top Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, p, -p);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-p, p, p);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(p, p, p);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(p, p, -p);  // Top Right Of The Texture and Quad
			// Bottom Face
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-p, -p, -p);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(p, -p, -p);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(p, -p, p);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-p, -p, p);  // Bottom Right Of The Texture and Quad
			// Right face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(p, -p, -p);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(p, p, -p);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(p, p, p);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(p, -p, p);  // Bottom Left Of The Texture and Quad
			// Left Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-p, -p, -p);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-p, -p, p);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-p, p, p);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, p, -p);  // Top Left Of The Texture and Quad
		glEnd();

	glPopMatrix();

}

void util::GLPrintMatrix4(float* matrix){
	std::string line1, line2, line3, line4;
	
	if (matrix[0] >= 0.0f) line1 += " ";
	line1 += std::to_string(matrix[0]) + ", ";
	if (matrix[1] >= 0.0f) line1 += " ";
	line1 += std::to_string(matrix[1]) + ", ";
	if (matrix[2] >= 0.0f) line1 += " ";
	line1 += std::to_string(matrix[2]) + ", ";
	if (matrix[3] >= 0.0f) line1 += " ";
	line1 += std::to_string(matrix[3]);
	
	
	if (matrix[4] >= 0.0f) line2 += " ";
	line2 += std::to_string(matrix[4]) + ", ";
	if (matrix[5] >= 0.0f) line2 += " ";
	line2 += std::to_string(matrix[5]) + ", ";
	if (matrix[6] >= 0.0f) line2 += " ";
	line2 += std::to_string(matrix[6]) + ", ";
	if (matrix[7] >= 0.0f) line2 += " ";
	line2 += std::to_string(matrix[7]);
	
	if (matrix[8] >= 0.0f) line3 += " ";
	line3 += std::to_string(matrix[8]) + ", ";
	if (matrix[9] >= 0.0f) line3 += " ";
	line3 += std::to_string(matrix[9]) + ", ";
	if (matrix[10] >= 0.0f) line3 += " ";
	line3 += std::to_string(matrix[10]) + ", ";
	if (matrix[11] >= 0.0f) line3 += " ";
	line3 += std::to_string(matrix[11]);

	if (matrix[12] >= 0.0f) line4 += " ";
	line4 += std::to_string(matrix[12]) + ", ";
	if (matrix[13] >= 0.0f) line4 += " ";
	line4 += std::to_string(matrix[13]) + ", ";
	if (matrix[14] >= 0.0f) line4 += " ";
	line4 += std::to_string(matrix[14]) + ", ";
	if (matrix[15] >= 0.0f) line4 += " ";
	line4 += std::to_string(matrix[15]);
	
	std::cout << "-------------Matrix-------------" << std::endl;
	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	std::cout << line4 << std::endl;
	std::cout << "-------------Matrix-------------" << std::endl;

	//printf("%s\n%s\n%s\n%s\n", lines[0], lines[1], lines[2],lines[3]);
}

float util::toFloat(const std::string& str){
	return (float)atof(str.c_str());
}

int util::toInt(const std::string& str){
	return atoi(str.c_str());
}

unsigned int util::toUInt(const std::string& str){
	return (unsigned int)atoi(str.c_str());
}

bool util::contains(std::istringstream& str, char ch){
	std::string line = str.str();
	return line.find(ch) != std::string::npos;
}

Vector2Df util::PixelToScreen(GLint x, GLint y){
	Vector2Df vec;

	vec.X = -1.0f + ((x / WINDOWWIDTH) * 2);
	vec.Y = -1.0f + ((y / WINDOWHEIGHT) * 2);

	return vec;
}