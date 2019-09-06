#include "Transform.h"

#include "Utils.h"

Transform::Transform() : rotation(), position() {
	
}

Transform::Transform(Vector3Df pos, Quaternion rot) 
	: position(pos), rotation(rot) {


}


void Transform::CreateTransformMatrix(float* matrix){
	rotation.CreateMatrix(matrix);

	matrix[12] = position.X;
	matrix[13] = position.Y;
	matrix[14] = position.Z;
	matrix[15] = 1.0f;
}

