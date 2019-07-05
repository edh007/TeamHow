/******************************************************************************/
/*!
\file   Matrix2x2.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Matrix4x4's class and members
Custom Matrix looks like this...

0  1
0	[ 00 10 ]
1	[ 01 11 ]

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _MATRIX2X2_H_
#define _MATRIX2X2_H_

#include <iostream>

struct Vector2;

//! Matrix2x2 struct
struct Matrix2x2
{
	//! Destructor
	~Matrix2x2(void);

	//! Constructors
	Matrix2x2(const float element = 0);
	Matrix2x2(const float member1, const float member2,
		const float member3, const float member4);
	Matrix2x2(const Matrix2x2& rhs);

	// Operators
	Matrix2x2& operator=(const Matrix2x2& rhs);
	Matrix2x2& operator-(void);

	Matrix2x2 operator+(const Matrix2x2& rhs) const;
	Matrix2x2 operator*(const Matrix2x2& rhs) const;
	Vector2 operator*(const Vector2& rhs) const;
	Matrix2x2 operator-(const Matrix2x2& rhs) const;

	Matrix2x2 operator+(const float constant) const;
	Matrix2x2 operator-(const float constant) const;
	Matrix2x2 operator*(const float constant) const;
	Matrix2x2 operator/(const float constant) const;

	// Transforming functions
	Matrix2x2 Transpose(void);
	void SetIdentity(void);

	// Frriend functions
	friend Matrix2x2 operator+(float constant, const Matrix2x2& rhs);
	friend Matrix2x2 operator*(float constant, const Matrix2x2& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Matrix2x2& contents);

	float m_member[2][2];
};

#endif // _MATRIX2X2_H_