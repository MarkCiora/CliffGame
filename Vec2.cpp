#include "Vec2.h"

#include <cmath>

Vec2::Vec2() {
	x = 0.;
	y = 0.;
}

Vec2::Vec2(float a, float b) {
	x = a;
	y = b;
}

Vec2 Vec2::operator+(const Vec2& added) const {
	Vec2 new_val;
	new_val.x = x + added.x;
	new_val.y = y + added.y;
	return new_val;
}
Vec2 Vec2::operator-(const Vec2& subtracted) const {
	Vec2 new_val;
	new_val.x = x - subtracted.x;
	new_val.y = y - subtracted.y;
	return new_val;
}
Vec2 Vec2::operator*(float mult) const {
	return Vec2(x * mult, y * mult);
}
Vec2 Vec2::operator/(float div) const {
	return Vec2(x / div, y / div);
}
Vec2& Vec2::operator=(const Vec2& new_val) {
	if (this == &new_val) return *this;
	x = new_val.x;
	y = new_val.y;
	return *this;
}
bool Vec2::operator==(const Vec2& vec) const {
	return (x == vec.x && y == vec.y);
}
ostream& operator<<(ostream& os, const Vec2& vec) {
	os << "(" << vec.x << ", " << vec.y << ") ";
	return os;
}

float Vec2::dot(const Vec2& a,const Vec2& b){
	return a.x * b.x + a.y + b.y;
}

float Vec2::mag() {
	return std::sqrt(x * x + y * y);
}

float Vec2::angle() {
	if (x == 0) {
		if (y > 0) return 3.141592654 / 2;
		else -3.141592654 / 2;
	}
	if (y > 0 && x > 0)return atan(y / x);
	if (y < 0 && x > 0)return atan(y / x);
	if (y > 0 && x < 0)return atan(y / x) + 3.141592654;
	if (y < 0 && x < 0)return atan(y / x) - 3.141592654;
}

Vec2 Vec2::normalized() {
	float m = mag();
	Vec2 vec;
	if (m == 0) {
		vec.x = 1;
		vec.y = 1;
	}
	else {
		vec = *this / m;
	}
	return vec;
}

Vec2 Vec2::VecFromAngle(float f) {
	Vec2 new_vec(cos(f), sin(f));
	return new_vec;
}