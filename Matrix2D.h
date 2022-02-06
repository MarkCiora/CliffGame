#pragma once

#include "Vec2.h"

class Matrix2D
{
public:
	float **data;
	Matrix2D();
	Matrix2D(float, float, float, float);
	Matrix2D(const Matrix2D&);
	~Matrix2D();

	float* operator[](int index);
	Vec2 operator*(const Vec2&);
	Matrix2D Transpose();

	static Matrix2D TransformFromAngle(float);
};
