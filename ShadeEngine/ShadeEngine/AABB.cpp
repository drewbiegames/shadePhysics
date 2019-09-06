#include "AABB.h"
#include "Utils.h"
#include "GLGameObject.h"

bool AABB::Collide(AABB& other){
	return 
		util::RangeIntersect(Max.X, Min.X, other.Max.X, other.Min.X) &&
		util::RangeIntersect(Max.Y, Min.Y, other.Max.Y, other.Min.Y) && 
		util::RangeIntersect(Max.Z, Min.Z, other.Max.Z, other.Min.Z);
}


void AABB::GLDraw(){
	
	glPushMatrix();
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.1f);
	
		//Front Face
		glBegin(GL_LINE_LOOP);
			glVertex3f(Min.X, Max.Y, Min.Z);
			glVertex3f(Max.X, Max.Y, Min.Z);
			glVertex3f(Max.X, Min.Y, Min.Z);
			glVertex3f(Min.X, Min.Y, Min.Z);
		glEnd();

		//Bottom Face
		glBegin(GL_LINE_LOOP);
			glVertex3f(Min.X, Max.Y, Max.Z);
			glVertex3f(Max.X, Max.Y, Max.Z);
			glVertex3f(Max.X, Max.Y, Min.Z);
			glVertex3f(Min.X, Max.Y, Min.Z);
		glEnd();

		//Left Face
		glBegin(GL_LINE_LOOP);
			glVertex3f(Max.X, Max.Y, Max.Z);
			glVertex3f(Max.X, Max.Y, Min.Z);
			glVertex3f(Max.X, Min.Y, Min.Z);
			glVertex3f(Max.X, Min.Y, Max.Z);
		glEnd();

		//Front Face
		glBegin(GL_LINE_LOOP);
			glVertex3f(Min.X, Max.Y, Max.Z);
			glVertex3f(Max.X, Max.Y, Max.Z);
			glVertex3f(Max.X, Min.Y, Max.Z);
			glVertex3f(Min.X, Min.Y, Max.Z);
		glEnd();

		//Bottom Face
		glBegin(GL_LINE_LOOP);
			glVertex3f(Min.X, Min.Y, Max.Z);
			glVertex3f(Max.X, Min.Y, Max.Z);
			glVertex3f(Max.X, Min.Y, Min.Z);
			glVertex3f(Min.X, Min.Y, Min.Z);
		glEnd();

		//Left Face
		glBegin(GL_LINE_LOOP);
			glVertex3f(Min.X, Max.Y, Max.Z);
			glVertex3f(Min.X, Max.Y, Min.Z);
			glVertex3f(Min.X, Min.Y, Min.Z);
			glVertex3f(Min.X, Min.Y, Max.Z);
		glEnd();

		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	
}

void AABB::CalculateAABB(){
	if (mCalcEachFrame){
		if (GLGameObject* obj = dynamic_cast<GLGameObject*>(Object)){
			Vector3Df pos = (*obj->getPosition());
			Vector3Df sizevechalf = (Max - Min) * 0.5f;

			Min = pos - (sizevechalf);
			Max = pos + (sizevechalf);
		}
	}
}