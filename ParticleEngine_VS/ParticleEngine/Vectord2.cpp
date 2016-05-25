#include "vectord2.h"
#include <math.h>

Vectord2::Vectord2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vectord2::Vectord2()
{
	x = 0;
	y = 0;
}


Vectord2::~Vectord2()
{
}

void Vectord2::operator=(const Vectord2 & rhs) 
{
	x = rhs.x;
	y = rhs.y;
}

void Vectord2::operator+=(const Vectord2 & rhs)
{
	x +=  rhs.x;
	y +=  rhs.y;
}

void Vectord2::operator*=(const double rhs)
{
	x *= rhs;
	y *= rhs;
}

void Vectord2::operator*=(const Vectord2 & rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

Vectord2 Vectord2::operator+(const Vectord2 &rhs) const
{
	Vectord2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	return temp;
}
Vectord2 Vectord2::operator-(const Vectord2 &rhs) const
{
	Vectord2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}
Vectord2 Vectord2::operator*(const double rhs) const
{
	Vectord2 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	return temp;
}
Vectord2 Vectord2::operator*(const Vectord2 &rhs) const
{
	Vectord2 temp;
	temp.x = x * rhs.x;
	temp.y = y * rhs.y;
	return temp;
}

Vectord2 Vectord2::operator/(const double rhs) const
{
	Vectord2 temp;
	temp.x = x / rhs;
	temp.y = y / rhs;
	return temp;
}

bool Vectord2::operator==(const Vectord2 & rhs) const

{
	return (fabsf(rhs.x - this->x) < EPSILON) && (fabsf(rhs.y - this->y) < EPSILON);
}

bool Vectord2::operator>(const Vectord2 & rhs) const
{
	return (this->x > rhs.x) && (this->y > rhs.y);
}

bool Vectord2::operator<(const Vectord2 & rhs) const
{
	return (this->x < rhs.x) && (this->y < rhs.y);
}

Vectord2 Vectord2::invert() const
{
	Vectord2 temp;
	temp.x = -x;
	temp.y = -y;
	return temp;
}

Vectord2& Vectord2::rotate(float angle)
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

Vectord2 Vectord2::Normalize() const
{
	Vectord2 temp;
	float length = this->Length();
	if (length < EPSILON && length > -EPSILON)
	{
		return Vectord2(0.0f, 0.0f);
	}
	temp.x = x / length;
	temp.y = y / length;
	return temp;
}

double Vectord2::Length() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Vectord2::SqrLength() const
{
	return pow(this->x, 2) + pow(this->y, 2);
}

double Vectord2::GetAngleRad() const
{
	return atan2f(y, x);;
}

double Vectord2::GetAngleDeg()const
{
	return (GetAngleRad() * 180.0f) / PI;
}
double Vectord2::dot(const Vectord2& rhs) const
{
	float a = this->x*rhs.x;
	float b = this->y*rhs.y;
	return a + b;
}

double Vectord2::det(const Vectord2 & rhs) const
{
	return this->x*rhs.y - this->y*rhs.x;
}

sf::Vector2f Vectord2::toVector2f() const
{
	sf::Vector2f vec2f;
	vec2f.x = this->x;
	vec2f.y = this->y;
	return vec2f;
}

sf::Vector2i Vectord2::toVector2i() const
{
	sf::Vector2i vec2i;
	vec2i.x = static_cast<int>(x);
	vec2i.y = static_cast<int>(y);
	return vec2i;
}

sf::Vector2u Vectord2::toVector2u() const
{
	sf::Vector2u vec2u;
	vec2u.x = static_cast<unsigned int>(x);
	vec2u.y = static_cast<unsigned int>(y);
	return vec2u;
}

Vector2 Vectord2::toVector2() const
{
	Vector2 vec2;
	vec2.x = static_cast<double>(x);
	vec2.y = static_cast<double>(y);
	return vec2;
}

Vectord2 Vectord2::rotate90() const
{
	if (x > 0)		return Vectord2(0 , 1);
	else if (x < 0) return Vectord2(0 , -1);
	else if (y > 0) return Vectord2(-1 , 0);
	else if (y < 0) return Vectord2(1 , 0);
	return Vectord2();
}

Vectord2& Vectord2::rotateAroundPoint(Vectord2 pivot, float angle)
{
	float theta = angle * PI / 180;
	
	*this += pivot * -1;
	rotate(angle);
	*this += pivot;
	
	return *this;
}
