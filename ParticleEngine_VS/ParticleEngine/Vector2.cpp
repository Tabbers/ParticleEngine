﻿#include "vector2.h"
#include "Vectord2.h"
#include <math.h>

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}


Vector2::~Vector2()
{
}

void Vector2::operator=(const Vector2 & rhs) 
{
	x = rhs.x;
	y = rhs.y;
}

void Vector2::operator+=(const Vector2 & rhs)
{
	x +=  rhs.x;
	y +=  rhs.y;
}

void Vector2::operator-=(const Vector2 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vector2::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
}

void Vector2::operator*=(const Vector2 & rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	return temp;
}
Vector2 Vector2::operator-(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}
Vector2 Vector2::operator-(const float & rhs) const
{
	Vector2 temp;
	temp.x = x;
	temp.y = y - rhs;
	return temp;
}
Vector2 Vector2::operator*(const float rhs) const
{
	Vector2 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	return temp;
}
Vector2 Vector2::operator*(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x * rhs.x;
	temp.y = y * rhs.y;
	return temp;
}

Vector2 Vector2::operator/(const float rhs) const
{
	Vector2 temp;
	temp.x = x / rhs;
	temp.y = y / rhs;
	return temp;
}

bool Vector2::operator==(const Vector2 & rhs) const

{
	return (fabsf(rhs.x - this->x) < EPSILON) && (fabsf(rhs.y - this->y) < EPSILON);
}

bool Vector2::operator>(const Vector2 & rhs) const
{
	return (this->x > rhs.x) && (this->y > rhs.y);
}

bool Vector2::operator<(const Vector2 & rhs) const
{
	return (this->x < rhs.x) && (this->y < rhs.y);
}

Vector2 Vector2::invert() const
{
	Vector2 temp;
	temp.x = -x;
	temp.y = -y;
	return temp;
}

Vector2& Vector2::rotate(float angle)
{

	angle *= PI/180.0f;

	float sinAngle = sinf(angle);
	float cosAngle = cosf(angle);

	float rX = this->x * cosAngle - this->y * sinAngle;
	float rY = this->x * sinAngle + this->y * cosAngle;

	this->x = rX;
	this->y = rY;
	return *this;
}

Vector2 Vector2::Normalize() const
{
	Vector2 temp;
	float length = this->Length();
	if (length < EPSILON && length > -EPSILON)
	{
		return Vector2(0.0f, 0.0f);
	}
	temp.x = x / length;
	temp.y = y / length;
	return temp;
}

float Vector2::Length() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

float Vector2::SqrLength() const 
{
	return pow(this->x, 2) + pow(this->y, 2);
}

float Vector2::GetAngleRad() const
{
	return atan2f(y, x);;
}

float Vector2::GetAngleDeg()const
{
	return (GetAngleRad() * 180.0f) / PI;
}
float Vector2::dot(const Vector2& rhs) const
{
	float a = this->x*rhs.x;
	float b = this->y*rhs.y;
	return a + b;
}

float Vector2::det(const Vector2 & rhs) const
{
	return this->x*rhs.y - this->y*rhs.x;
}

sf::Vector2f Vector2::toVector2f() const
{
	sf::Vector2f vec2f;
	vec2f.x = this->x;
	vec2f.y = this->y;
	return vec2f;
}

sf::Vector2i Vector2::toVector2i() const
{
	sf::Vector2i vec2i;
	vec2i.x = static_cast<int>(x);
	vec2i.y = static_cast<int>(y);
	return vec2i;
}

sf::Vector2u Vector2::toVector2u() const
{
	sf::Vector2u vec2u;
	vec2u.x = static_cast<unsigned int>(x);
	vec2u.y = static_cast<unsigned int>(y);
	return vec2u;
}

Vectord2 Vector2::toVectord2() const
{
	Vectord2 vecd2;
	vecd2.x = static_cast<float>(x);
	vecd2.y = static_cast<float>(y);
	return vecd2;
}

Vector2 Vector2::rotate90() const
{
	if (x > 0)		return Vector2(0 , 1);
	else if (x < 0) return Vector2(0 , -1);
	else if (y > 0) return Vector2(-1 , 0);
	else if (y < 0) return Vector2(1 , 0);
	return Vector2();
}

Vector2& Vector2::rotateAroundPoint(Vector2 pivot, float angle)
{
	float theta = angle * PI / 180;
	
	*this += pivot * -1;
	rotate(angle);
	*this += pivot;
	
	return *this;
}
