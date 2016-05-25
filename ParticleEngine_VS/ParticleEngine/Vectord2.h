#pragma once
#include "Vector2.h"
class Vector2;
#ifndef SFML_VECTOR2_HPP
#define SFML_VECTOR2_HPP


namespace sf
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T X, T Y);
		template <typename U>
		explicit Vector2(const Vector2<U>& vector);
		// Member data
		T x;
		T y;
	};
	template <typename T>
	Vector2<T> operator -(const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator *(const Vector2<T>& left, T right);

	template <typename T>
	Vector2<T> operator *(T left, const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator *=(Vector2<T>& left, T right);

	template <typename T>
	Vector2<T> operator /(const Vector2<T>& left, T right);

	template <typename T>
	Vector2<T>& operator /=(Vector2<T>& left, T right);

	template <typename T>
	bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

#include <SFML/System/Vector2.inl>
	// Define the most common types
	typedef Vector2<int>          Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<float>        Vector2f;
} // namespace sf
#endif // SFML_VECTOR2_HPP

class Vectord2
{
public:
	 Vectord2(float,float);
	 Vectord2();
	 ~Vectord2();
	 void operator=(const Vectord2 &rhs);
	 void operator+=(const Vectord2 &rhs);
	 void operator*=(const double);
	 void operator*=(const Vectord2 &rhs);
	 Vectord2 operator+(const Vectord2 &rhs) const;
	 Vectord2 operator-(const Vectord2 &rhs) const;
	 Vectord2 operator*(const double rhs)   const;
	 Vectord2 operator*(const Vectord2 &rhs) const;
	 Vectord2 operator/(const double rhs)   const;
	 bool operator==(const Vectord2 &rhs)   const;
	 bool operator>(const Vectord2 &rhs)    const;
	 bool operator<(const Vectord2 &rhs)    const;
	 Vectord2 invert()					   const;
	 Vectord2 rotate90()					   const;
	 Vectord2& rotateAroundPoint(Vectord2 pivot, float angle);
	 Vectord2& rotate(float); 
	 Vectord2 Normalize()				   const;
	 double Length()					   const;
	 double SqrLength()					   const;
	 double GetAngleRad()				   const;
	 double GetAngleDeg()				   const;
	 double dot(const Vectord2& rhs)		   const;
	 double det(const Vectord2& rhs)		   const;
	 sf::Vector2f toVector2f()			   const;
	 sf::Vector2i toVector2i()			   const;
	 sf::Vector2u toVector2u()			   const;
	 Vector2 toVector2() const;
public:
	float x = 0;
	float y = 0;
	const float PI = 3.1415927410125732421875f;
	const float EPSILON = 0.001;
};

