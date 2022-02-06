#pragma once

#include <iostream>

using std::ostream;

class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float, float);

	Vec2 operator+(const Vec2&) const;
	Vec2 operator-(const Vec2&) const;
	Vec2 operator*(float) const;
	Vec2 operator/(float) const;
	Vec2& operator=(const Vec2&);
	bool operator==(const Vec2&) const;
	friend ostream& operator<<(ostream&, const Vec2&);

	static float dot(const Vec2&,const Vec2&);
	float mag();
	float angle();
	Vec2 normalized();

	static Vec2 VecFromAngle(float);
};
