/******************************************************************************/
/*!
\file   Vector4.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Vector4's template class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

struct Vector2;

template <typename Type>
class Vector3;

//! class template Vector4
template <typename Type>
class Vector4
{
public:

	// Constructors and destructor
	~Vector4(void);
	Vector4(Type _x = 0, Type _y = 0, Type _z = 0, Type _w = 0);
	Vector4(const Vector2& rhs, Type _z = 0, Type _w = 0);
	Vector4(const Vector3<Type>& rhs, Type _w = 0);
	Vector4(const Vector4<Type>& rhs);

	// Operators
	Vector4& operator=(const Vector4& rhs);
	Vector4& operator-(void);
	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator+=(const Type& constant);
	Vector4& operator-=(const Vector4& rhs);
	Vector4& operator-=(const Type& constant);
	Vector4& operator*=(const Type& constant);

	Vector4 operator+(const Vector4& rhs) const;
	Vector4 operator+(const Type& constant) const;

	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator-(const Type& constant) const;

	Vector4 operator*(const Type& constant) const;
	Vector4 operator/(const Type& constant) const;

	// Trasnforming functions and helpers
	Type Length(void) const;
	Type DotProduct(const Vector4& rhs);
	Vector4<Type> Normalize(void);

	// Friend functions
	template <typename Type>
	friend Vector4<Type> operator+(Type constant, Vector4<Type>& rhs);

	template <typename Type>
	friend Vector4<Type> operator*(Type constant, Vector4<Type>& rhs);
	
	template <typename Type>
	friend std::ostream& operator<<(std::ostream& os, const Vector4<Type>& contents);

	Type x, y, z, w;

private:
	
};

#include "Vector4.cpp"

#endif // _MATRIX_H_