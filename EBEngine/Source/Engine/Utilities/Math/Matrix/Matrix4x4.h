/******************************************************************************/
/*!
\file   Matrix4x4.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Matrix4x4's template class and members
Custom Matrix looks like this...

0  1  2  3
0	[ 00 10 20 30 ]
1	[ 01 11 21 31 ]
2	[ 02 12 22 32 ]
3	[ 03 13 23 33 ]

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

template <typename Type>
class Vector3;

template <typename Type>
class Vector4;

//! Matrix 4x4 template class
template <typename Type>
class Matrix4x4
{
public:

	//! cons and des
	Matrix4x4(void);
	~Matrix4x4(void);

	// Copy cons
	Matrix4x4(const Type& element);
	Matrix4x4(const Matrix4x4& rhs);

	// Operators
	Matrix4x4& operator=(const Matrix4x4& rhs);
	Matrix4x4& operator-(void);

	Matrix4x4 operator+(const Matrix4x4& rhs) const;
	Matrix4x4 operator*(const Matrix4x4& rhs) const;
	Vector4<Type> operator*(const Vector4<Type>& rhs) const;
	Matrix4x4 operator-(const Matrix4x4& rhs) const;

	Matrix4x4 operator+(const Type& constant) const;
	Matrix4x4 operator-(const Type& constant) const;
	Matrix4x4 operator*(const Type& constant) const;
	Matrix4x4 operator/(const Type& constant) const;

	// Transforming functions
	// Matrix settor
	Matrix4x4 Transpose(void);
	void SetIdentity(void);

	// To use graphic...
	static Matrix4x4<Type> Translate(const Vector3<Type>& vec);
	static Matrix4x4<Type> Scale(const Vector3<Type>& vec);
	static Matrix4x4<Type> Rotation(float degree, Vector3<Type>& vec);
	static Matrix4x4<Type> Perspective(float const & fovy, float const & aspect, float const & zNear, float const & zFar);
	static Matrix4x4<Type> Ortho(float const & left, float const & right, float const& bottom, float const& top, float const & zNear, float const & zFar);
	static Matrix4x4<Type> LookAt(Vector3<Type> eye, Vector3<Type> center, Vector3<Type> up);


	//Friend functions
	template <typename Type>
	friend Matrix4x4<Type> operator+(Type constant, const Matrix4x4<Type>& rhs);

	template <typename Type>
	friend Matrix4x4<Type> operator*(Type constant, const Matrix4x4<Type>& rhs);

	template <typename Type>
	friend std::ostream& operator<<(std::ostream& os, const Matrix4x4<Type>& contents);

	Type m_member[4][4];

private:

};

#include "Matrix4x4.cpp"

#endif // _MATRIX4X4_H_
