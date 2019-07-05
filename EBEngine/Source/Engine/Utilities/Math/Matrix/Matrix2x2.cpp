/******************************************************************************/
/*!
\file   Matrix2x2.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Matrix2x2's class and member function
Custom Matrix looks like this...

		   0  1  
	0	[ 00 10 ]
	1	[ 01 11 ]

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Matrix2x2.h"
#include "../Vector/Vector2.h"

/******************************************************************************/
/*!
\brief - Matrix2x2 Destructor
*/
/******************************************************************************/
Matrix2x2::~Matrix2x2(void)
{}

/******************************************************************************/
/*!
\brief - Matrix2x2 Constructor
\param element - to be element(all 4 elements)
*/
/******************************************************************************/
Matrix2x2::Matrix2x2(const float element)
{
	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		m_member[i][j] = element;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 Constructor
\param member1 - member[0][0]
\param member2 - member[0][1]
\param member3 - member[1][0]
\param member4 - member[1][1]
*/
/******************************************************************************/
Matrix2x2::Matrix2x2(const float member1, const float member2,
	const float member3, const float member4)
{
	m_member[0][0] = member1;
	m_member[0][1] = member2;
	m_member[1][0] = member3;
	m_member[1][1] = member4;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 Copy Constructor
\param rhs - to be copied
*/
/******************************************************************************/
Matrix2x2::Matrix2x2(const Matrix2x2& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}
}

/******************************************************************************/
/*!
\brief - Matrix2x2 = operator
\param rhs - to be assigned
\return *this
*/
/******************************************************************************/
Matrix2x2& Matrix2x2::operator=(const Matrix2x2& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}

	return *this;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 unary - operator
\return *this
*/
/******************************************************************************/
Matrix2x2& Matrix2x2::operator - (void)
{
	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		m_member[i][j] = -m_member[i][j];

	return *this;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 + operator
\param rhs - matrix to add
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator+(const Matrix2x2& rhs) const
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] + rhs.m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 * operator
\param rhs - matrix to multiply
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator*(const Matrix2x2& rhs) const
{
	Matrix2x2 result;

	result.m_member[0][0] = m_member[0][0] * rhs.m_member[0][0] + m_member[0][1] * rhs.m_member[1][0];
	result.m_member[0][1] = m_member[0][0] * rhs.m_member[0][1] + m_member[0][1] * rhs.m_member[1][1];
	result.m_member[1][0] = m_member[1][0] * rhs.m_member[0][0] + m_member[1][1] * rhs.m_member[1][0];
	result.m_member[1][1] = m_member[1][0] * rhs.m_member[0][1] + m_member[1][1] * rhs.m_member[1][1];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 * operator with vector2
\param rhs - vector2 to multiply 
\return result
*/
/******************************************************************************/
Vector2 Matrix2x2::operator*(const Vector2& rhs) const
{
	Vector2 result;

	result.x = m_member[0][0] * rhs.x + m_member[0][1] * rhs.y ;
	result.y = m_member[1][0] * rhs.x + m_member[1][1] * rhs.y ;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 - operator 
\param rhs - matrix to subtract
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator-(const Matrix2x2& rhs) const
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] - rhs.m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 + operator
\param rhs - number to add
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator+(const float constant) const
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 - operator
\param rhs - number to subtract
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator-(const float constant) const
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] - constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 * operator
\param rhs - number to multiply
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator*(const float constant) const
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] * constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix2x2 / operator
\param rhs - number to divide
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::operator/(const float constant) const
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] / constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Transpose matrix
\return result
*/
/******************************************************************************/
Matrix2x2 Matrix2x2::Transpose(void)
{
	Matrix2x2 result;

	result.m_member[0][0] = m_member[0][0];
	result.m_member[0][1] = m_member[1][0];
	result.m_member[1][0] = m_member[0][1];
	result.m_member[1][1] = m_member[1][1];

	return result;
}

/******************************************************************************/
/*!
\brief - Set identity matrix
*/
/******************************************************************************/
void Matrix2x2::SetIdentity(void) 
{
	m_member[0][0] = 1;
	m_member[0][1] = 0;
	m_member[1][0] = 0;
	m_member[1][1] = 1;
}

/******************************************************************************/
/*!
\brief - Friend function, + operator 
\param constant - number to add
\param rhs - *this 
\return result
*/
/******************************************************************************/
Matrix2x2 operator+(float constant, const Matrix2x2& rhs)
{
	Matrix2x2 result;
	result = rhs + constant;
	return result;
}

/******************************************************************************/
/*!
\brief - Friend function, * operator
\param constant - number to multiply
\param rhs - *this
\return result
*/
/******************************************************************************/
Matrix2x2 operator*(float constant, const Matrix2x2& rhs)
{
	Matrix2x2 result;
	result = rhs * constant;
	return result;
}

/******************************************************************************/
/*!
\brief - Friend function, << operator
\param os - storage to put contents
\param rhs - contents to print out
\return os
*/
/******************************************************************************/
std::ostream& operator<<(std::ostream& os, const Matrix2x2& contents)
{
	for (int i = 0; i < 2; ++i)
	{
		os << "[ ";
		for (int j = 0; j < 2; ++j)
		{
			os.setf(std::ios_base::showpoint);
			os << contents.m_member[i][j] << " ";
		}
		os << "]\n";
	}

	return os;
}