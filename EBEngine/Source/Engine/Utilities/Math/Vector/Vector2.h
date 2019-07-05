/******************************************************************************/
/*!
\file   Vector2.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Vector2's class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <iostream>

template <typename Type>
class Vector3;

//! vector2 struct
struct Vector2
{
	// Constructors and destructor
	Vector2(float _x = 0, float _y = 0);
	Vector2(const Vector2& copy);
	Vector2(const Vector3<float>& copy);
	~Vector2(void);

	// Operators
	bool operator<(const Vector2& rhs) const;
	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;
	Vector2& operator=(const Vector2& rhs);
	Vector2& operator-(void);
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator+=(const float constant);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator-=(const float constant);
	Vector2& operator*=(const float constant);

	Vector2 operator+(const float constant) const;
	Vector2 operator+(const Vector2& rhs) const;

	Vector2 operator-(const float constant) const;
	Vector2 operator-(const Vector2& rhs) const;

	Vector2 operator*(const float constant) const;
	Vector2 operator/(const float constant) const;

	// Transform functions
	float Length(void) const;
	float DotProduct(const Vector2& rhs);
	Vector2 CrossProduct(const Vector2& rhs);
	Vector2 Normalize(void);

	//! Friend functions
	friend Vector2 operator+(float constant, const Vector2& rhs);
	friend Vector2 operator*(float constant, const Vector2& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector2& constents);

	float x, y;
};

#endif // _VECTOR_H_