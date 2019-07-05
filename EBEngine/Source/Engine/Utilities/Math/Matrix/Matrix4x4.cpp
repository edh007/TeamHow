/******************************************************************************/
/*!
\file   Matrix4x4.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Matrix4x4's template class and member function
Custom Matrix looks like this...

		  0  1  2  3
	0	[ 00 10 20 30 ]
	1	[ 01 11 21 31 ]
	2	[ 02 12 22 32 ]
	3	[ 03 13 23 33 ]

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../Vector/Vector3.h"
#include "../Vector/Vector4.h"
#include "Matrix4x4.h"

/******************************************************************************/
/*!
\brief - Matrix4x4 Constructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::Matrix4x4(void)
{
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = 0;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 Destructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::~Matrix4x4(void)
{}

/******************************************************************************/
/*!
\brief - Matrix4x4 Constructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::Matrix4x4(const Type& element)
{
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = element;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 Copy Constructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::Matrix4x4(const Matrix4x4<Type>& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}
}

/******************************************************************************/
/*!
\brief - Matrix4x4 = operator 
\param rhs - matrix to assign
\return *this
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>& Matrix4x4<Type>::operator = (const Matrix4x4<Type>& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}

	return *this;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 - unary operator
\return *this
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>& Matrix4x4<Type>::operator-(void)
{
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = -m_member[i][j];

	return *this;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 + operator
\param rhs - matrix to add
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator + (const Matrix4x4<Type>& rhs) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = m_member[i][j] + rhs.m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 + operator
\param rhs - number to add
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator + (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 - operator
\param rhs - matrix to subtract
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator - (const Matrix4x4<Type>& rhs) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] - rhs.m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 - operator
\param rhs - number to subtract
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator - (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] - constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 * operator
\param rhs - number to multiply
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator * (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] * constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 * operator
\param rhs - matrix to multiply
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator*(const Matrix4x4<Type>& rhs) const
{
	Matrix4x4 result;

	result.m_member[0][0] = m_member[0][0] * rhs.m_member[0][0] + m_member[0][1] * rhs.m_member[1][0] + m_member[0][2] * rhs.m_member[2][0] + m_member[0][3] * rhs.m_member[3][0];
	result.m_member[0][1] = m_member[0][0] * rhs.m_member[0][1] + m_member[0][1] * rhs.m_member[1][1] + m_member[0][2] * rhs.m_member[2][1] + m_member[0][3] * rhs.m_member[3][1];
	result.m_member[0][2] = m_member[0][0] * rhs.m_member[0][2] + m_member[0][1] * rhs.m_member[1][2] + m_member[0][2] * rhs.m_member[2][2] + m_member[0][3] * rhs.m_member[3][2];
	result.m_member[0][3] = m_member[0][0] * rhs.m_member[0][3] + m_member[0][1] * rhs.m_member[1][3] + m_member[0][2] * rhs.m_member[2][3] + m_member[0][3] * rhs.m_member[3][3];

	result.m_member[1][0] = m_member[1][0] * rhs.m_member[0][0] + m_member[1][1] * rhs.m_member[1][0] + m_member[1][2] * rhs.m_member[2][0] + m_member[1][3] * rhs.m_member[3][0];
	result.m_member[1][1] = m_member[1][0] * rhs.m_member[0][1] + m_member[1][1] * rhs.m_member[1][1] + m_member[1][2] * rhs.m_member[2][1] + m_member[1][3] * rhs.m_member[3][1];
	result.m_member[1][2] = m_member[1][0] * rhs.m_member[0][2] + m_member[1][1] * rhs.m_member[1][2] + m_member[1][2] * rhs.m_member[2][2] + m_member[1][3] * rhs.m_member[3][2];
	result.m_member[1][3] = m_member[1][0] * rhs.m_member[0][3] + m_member[1][1] * rhs.m_member[1][3] + m_member[1][2] * rhs.m_member[2][3] + m_member[1][3] * rhs.m_member[3][3];

	result.m_member[2][0] = m_member[2][0] * rhs.m_member[0][0] + m_member[2][1] * rhs.m_member[1][0] + m_member[2][2] * rhs.m_member[2][0] + m_member[2][3] * rhs.m_member[3][0];
	result.m_member[2][1] = m_member[2][0] * rhs.m_member[0][1] + m_member[2][1] * rhs.m_member[1][1] + m_member[2][2] * rhs.m_member[2][1] + m_member[2][3] * rhs.m_member[3][1];
	result.m_member[2][2] = m_member[2][0] * rhs.m_member[0][2] + m_member[2][1] * rhs.m_member[1][2] + m_member[2][2] * rhs.m_member[2][2] + m_member[2][3] * rhs.m_member[3][2];
	result.m_member[2][3] = m_member[2][0] * rhs.m_member[0][3] + m_member[2][1] * rhs.m_member[1][3] + m_member[2][2] * rhs.m_member[2][3] + m_member[2][3] * rhs.m_member[3][3];

	result.m_member[3][0] = m_member[3][0] * rhs.m_member[0][0] + m_member[3][1] * rhs.m_member[1][0] + m_member[3][2] * rhs.m_member[2][0] + m_member[3][3] * rhs.m_member[3][0];
	result.m_member[3][1] = m_member[3][0] * rhs.m_member[0][1] + m_member[3][1] * rhs.m_member[1][1] + m_member[3][2] * rhs.m_member[2][1] + m_member[3][3] * rhs.m_member[3][1];
	result.m_member[3][2] = m_member[3][0] * rhs.m_member[0][2] + m_member[3][1] * rhs.m_member[1][2] + m_member[3][2] * rhs.m_member[2][2] + m_member[3][3] * rhs.m_member[3][2];
	result.m_member[3][3] = m_member[3][0] * rhs.m_member[0][3] + m_member[3][1] * rhs.m_member[1][3] + m_member[3][2] * rhs.m_member[2][3] + m_member[3][3] * rhs.m_member[3][3];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 * operator with vector4
\param rhs - vector4 to multiply
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Matrix4x4<Type>::operator*(const Vector4<Type>& rhs) const
{
	Vector4<Type> result;

	result.x = m_member[0][0] * rhs.x + m_member[0][1] * rhs.y + m_member[0][2] * rhs.z + m_member[0][3] * rhs.w;
	result.y = m_member[1][0] * rhs.x + m_member[1][1] * rhs.y + m_member[1][2] * rhs.z + m_member[1][3] * rhs.w;
	result.z = m_member[2][0] * rhs.x + m_member[2][1] * rhs.y + m_member[2][2] * rhs.z + m_member[2][3] * rhs.w;
	result.w = m_member[3][0] * rhs.x + m_member[3][1] * rhs.y + m_member[3][2] * rhs.z + m_member[3][3] * rhs.w;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 / operator 
\param rhs - number to divide
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator / (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] / constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Set matrix identity
*/
/******************************************************************************/
template <typename Type>
void Matrix4x4<Type>::SetIdentity(void)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
				m_member[i][j] = 1;
			else
				m_member[i][j] = 0;
		}
	}
}

/******************************************************************************/
/*!
\brief - Friend function + operator
\param constant - number to add
\param rhs - this
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> operator+(Type constant, const Matrix4x4<Type>& rhs)
{
	Matrix4x4<Type> result;

	result = rhs + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Friend function * operator
\param constant - number to multiply
\param rhs - this
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> operator*(Type constant, const Matrix4x4<Type>& rhs)
{
	Matrix4x4<Type> result;
	result = rhs * constant;
	return result;
}

/******************************************************************************/
/*!
\brief - Friend function << operator
\param os - storage to put contents
\param contents - contents to print out
\return os
*/
/******************************************************************************/
template <typename Type>
std::ostream& operator<<(std::ostream& os, const Matrix4x4<Type>& contents)
{
	for (int i = 0; i < 4; ++i)
	{
		os << "[ ";
		for (int j = 0; j < 4; ++j)
		{
			os.setf(std::ios_base::showpoint);
			os << contents.m_member[i][j] << " ";
		}
		os << "]\n";
	}

	return os;
}

/******************************************************************************/
/*!
\brief - Transpose matrix
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Transpose(void)
{
	Matrix4x4 result;

	result = *this;
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[j][i] = m_member[i][j];

	return result;
}

template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Perspective(float const & fovy, float const & aspect, float const & zNear, float const & zFar)
{
	float tanHalfFovy = tan(fovy / static_cast<float>(2));

	Matrix4x4<Type> Result(static_cast<float>(0));
	Result.m_member[0][0] = static_cast<float>(1) / (aspect * tanHalfFovy);
	Result.m_member[1][1] = static_cast<float>(1) / (tanHalfFovy);
	Result.m_member[2][2] = -(zFar + zNear) / (zFar - zNear);
	Result.m_member[2][3] = -static_cast<float>(1);
	Result.m_member[3][2] = -(static_cast<float>(2) * zFar * zNear) / (zFar - zNear);
	return Result;
}

template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Ortho(float const & left, float const & right, float const& bottom, float const& top, float const & zNear, float const & zFar)
{
	//tmat4x4<T, defaultp> Result(1);
	//Result[0][0] = static_cast<T>(2) / (right - left);
	//Result[1][1] = static_cast<T>(2) / (top - bottom);
	//Result[2][2] = -static_cast<T>(2) / (zFar - zNear);
	//Result[3][0] = -(right + left) / (right - left);
	//Result[3][1] = -(top + bottom) / (top - bottom);
	//Result[3][2] = -(zFar + zNear) / (zFar - zNear);

	Matrix4x4 Result;
	Result.m_member[0][0] = static_cast<Type>(2) / (right - left);
	Result.m_member[1][1] = static_cast<Type>(2) / (top - bottom);
	Result.m_member[2][2] = -static_cast<Type>(2) / (zFar - zNear);
	Result.m_member[3][0] = (-(right + left)) / (right - left);
	Result.m_member[3][1] = (-(top + bottom)) / (top - bottom);
	Result.m_member[3][2] = (-(zFar + zNear)) / (zFar - zNear);
	Result.m_member[3][3] = static_cast<Type>(1);
	return Result;
}

template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::LookAt(Vector3<Type> eye, Vector3<Type> center, Vector3<Type> up)
{
	Vector3<Type> temp = (center - eye);

	Vector3<Type> f = temp.Normalize();
	Vector3<Type> cal = f.CrossProduct(up);
	Vector3<Type> s = cal * 1 / (sqrt(cal.DotProduct(cal)));
	//		return x * inversesqrt(dot(x, x));
	Vector3<Type> u = s.CrossProduct(f);

	Matrix4x4<Type> Result;
	Result.SetIdentity();

	Result.m_member[0][0] = s.x;
	Result.m_member[1][0] = s.y;
	Result.m_member[2][0] = s.z;

	Result.m_member[0][1] = u.x;
	Result.m_member[1][1] = u.y;
	Result.m_member[2][1] = u.z;

	Result.m_member[0][2] = -f.x;
	Result.m_member[1][2] = -f.y;
	Result.m_member[2][2] = -f.z;

	Result.m_member[3][0] = -(s.DotProduct(eye));
	Result.m_member[3][1] = -(u.DotProduct(eye));
	Result.m_member[3][2] = f.DotProduct(eye);

	return Result;
}

template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Translate(const Vector3<Type>& vec)
{
	Matrix4x4 Result;
	Result.SetIdentity();

	Result.m_member[3][0] = vec.x;
	Result.m_member[3][1] = vec.y;
	Result.m_member[3][2] = vec.z;

	return Result;
}

template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Scale(const Vector3<Type>& vec)
{
	Matrix4x4 Result;
	Result.SetIdentity();

	Result.m_member[0][0] = vec.x;
	Result.m_member[1][1] = vec.y;
	Result.m_member[2][2] = vec.z;

	return Result;
}

template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Rotation(float degree, Vector3<Type>& vec)
{
	Matrix4x4 Result;
	Result.SetIdentity();

	float c = cos(degree);
	float s = sin(degree);

	Vector3<Type> a = vec.Normalize();
	Vector3<Type> n = ((Type(1) - c) * a);

	Result.m_member[0][0] = c + n.x + a.x;
	Result.m_member[0][1] = n.x * a.y + s * a.z;
	Result.m_member[0][2] = n.x * a.z - s * a.y;

	Result.m_member[1][0] = n.y * a.x - s * a.z;
	Result.m_member[1][1] = c + n.y * a.y;
	Result.m_member[1][2] = n.y * a.z + s * a.x;

	Result.m_member[2][0] = n.z * a.x + s * a.y;
	Result.m_member[2][1] = n.z * a.y - s * a.x;
	Result.m_member[2][2] = c + n.z * a.z;

	return Result;
}