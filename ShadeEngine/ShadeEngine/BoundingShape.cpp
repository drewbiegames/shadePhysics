#include "BoundingShape.h"

#include "Circle.h"
#include "Rectangle.h"
#include "AABB.h"
#include "OBB.h"
#include "Sphere.h"
#include "Capsule.h"

//Ensures the correct collision test is called
//	Param 1 - Bounding Shape to be tested
bool BoundingShape::Collide(BoundingShape* other){
	if (Circle* circle = dynamic_cast<Circle*>(other)){
		return Collide((*circle));
	}
	else if (MyRectangle* rect = dynamic_cast<MyRectangle*>(other)){
		return Collide((*rect));
	}
	else if (AABB* aabb = dynamic_cast<AABB*>(other)){
		return Collide((*aabb));
	}
	else if (Sphere* sphere = dynamic_cast<Sphere*>(other)){
		return Collide((*sphere));
	}
	else if (Capsule* capsule = dynamic_cast<Capsule*>(other)){
		return Collide((*capsule));
	}
	else if (OBB* obb = dynamic_cast<OBB*>(other)){
		return Collide((*obb));
	}
	else{
		return false;
	}
}