#include "Matrix2D.h"

#include <cmath>

Matrix2D::Matrix2D() {
	data = new float* [2];
	data[0] = new float[2];
	data[1] = new float[2];
}
Matrix2D::Matrix2D(float a, float b, float c, float d) {
	data = new float*[2];
	data[0] = new float[2];
	data[1] = new float[2];
	data[0][0] = a;
	data[0][1] = b;
	data[1][0] = c;
	data[1][1] = d;
}
Matrix2D::Matrix2D(const Matrix2D &copy){
	data = new float*[2];
	data[0] = new float[2];
	data[1] = new float[2];
	data[0][0] = copy.data[0][0];
	data[0][1] = copy.data[0][1];
	data[1][0] = copy.data[1][0];
	data[1][1] = copy.data[1][1];
}
Matrix2D::~Matrix2D() {
	delete [] data[0];
	delete [] data[1];
	delete [] data;
}

float* Matrix2D::operator[](int index) {
	return data[index];
}

Vec2 Matrix2D::operator*(const Vec2 &vec) {
	Vec2 ret;
	ret.x = vec.x * data[0][0] + vec.y * data[0][1];
	ret.y = vec.x * data[1][0] + vec.y * data[1][1];
	return ret;
}

Matrix2D Matrix2D::Transpose(){
	Matrix2D mat(*this);
	auto temp = data[0][1];
	data[0][1] = data[1][0];
	data[1][0] = temp;
	return mat;
}

Matrix2D Matrix2D::TransformFromAngle(float angle) {
	float sin_angle = sin(angle);
	float cos_angle = cos(angle);
	return Matrix2D(cos_angle, -sin_angle, sin_angle, cos_angle);
}