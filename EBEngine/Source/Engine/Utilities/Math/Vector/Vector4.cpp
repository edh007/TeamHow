/******************************************************************************/
/*!
\file   Vector4.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Vector4's template class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Vector3.h"
#include "Vector4.h"

/******************************************************************************/
/*!
\brief - Vector4 Destructor
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>::~Vector4(void)
{}

/******************************************************************************/
/*!
\brief - Vector4 Constructor
\param _x - element x
\param _y - element y
\param _z - element z
\param _w - element w
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>::Vector4(Type _x, Type _y, Type _z, Type _w)
	:x(_x), y(_y), z(_z), w(_w)
{}

/******************************************************************************/
/*!
\brief - Vector4 Constructor
\param vec - Vector2
\param _z - element z
\param _w - element w
*/
/******************************************************************************/
template<typename Type>
Vector4<Type>::Vector4(const Vector2& rhs, Type _z = 0, Type _w = 0)
	: x(rhs.x), y(rhs.y), z(_z), w(_w)
{
}

/******************************************************************************/
/*!
\brief - Vector4 Constructor
\param vec - Vector3
\param _w - element w
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>::Vector4(const Vector3<Type>& vec, Type _w = 0)
	: x(vec.x), y(vec.y), z(vec.z), w(_w)
{}

/******************************************************************************/
/*!
\brief - Vector4 Copy Constructor
\param copy - Vector4 to be copied
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>::Vector4(const Vector4<Type>& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}
}

/******************************************************************************/
/*!
\brief - Vector4 = operator
\param rhs - Vector4 to be assigned
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator=(const Vector4<Type>& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector4 unary - operator
\param rhs - Vector4 to be assigned
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator-(void)
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector4 + operator
\param rhs - number to be added
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::operator+(const Vector4<Type>& rhs) const
{
	Vector4 result;

	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;
	result.w = w + rhs.w;

	return result;
}

/******************************************************************************/
/*!
\brief - Vector4 + operator
\param rhs - Vector4 to be added
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::operator+(const Type& constant) const
{
	Vector4 result;

	result.x = x + constant;
	result.y = y + constant;
	result.z = z + constant;
	result.w = w + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Vector4 - operator
\param rhs - Vector4 to be subtracted
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::operator-(const Vector4<Type>& rhs) const
{
	Vector4 result;

	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;
	result.w = w - rhs.w;

	return result;
}

/******************************************************************************/
/*!
\brief - Vector4 - operator
\param rhs - number to be subtracted
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::operator-(const Type& constant) const
{
	Vector4 result;

	result.x = x - constant;
	result.y = y - constant;
	result.z = z - constant;
	result.w = w - constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Vector4 * operator
\param rhs - number to be nultiplied
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::operator*(const Type& constant) const
{
	Vector4 result;

	result.x = x * constant;
	result.y = y * constant;
	result.z = z * constant;
	result.w = w * constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Vector4 / operator
\param rhs - number to be divided
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::operator / (const Type& constant) const
{
	Vector4 result;

	result.x = x / constant;
	result.y = y / constant;
	result.z = z / constant;
	result.w = w / constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Friend function, + operator
\param constant - number to be added
\param rhs - *this
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> operator+(Type constant, const Vector4<Type>& rhs)
{
	Vector4<Type> result;

	result = rhs + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Friend function, * operator
\param constant - number to be multiplied
\param rhs - *this
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> operator*(Type constant, const Vector4<Type>& rhs)
{
	Vector4<Type> result;

	result = rhs * constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Friend function, << operator
\param constant - storage to put contents in
\param rhs - *this
\return os
*/
/******************************************************************************/
template <typename Type>
std::ostream& operator<<(std::ostream& os, const Vector4<Type>& contents)
{
	os << "Vector4[ " << contents.x << ", " << contents.y << ", " << contents.z << ", " << contents.w << " ]";
	return os;
}

/******************************************************************************/
/*!
\brief - Get two Vector4s' DotProduct
\param rhs - to be calculated
\return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
*/
/******************************************************************************/
template <typename Type>
Type Vector4<Type>::DotProduct(const Vector4& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

/******************************************************************************/
/*!
\brief - Vector4 += operator
\param rhs - Vector4 to be added
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector4 += operator
\param rhs - number to be added
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator+=(const Type& constant)
{
	x += constant;
	y += constant;
	z += constant;
	w += constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector4 -= operator
\param rhs - Vector4 to be subtracted
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector4 -= operator
\param rhs - number to be subtracted
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator-=(const Type& constant)
{
	x -= constant;
	y -= constant;
	z -= constant;
	w -= constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector4 *= operator
\param rhs - Vector4 to be multiplied
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Type& constant)
{
	x *= constant;
	y *= constant;
	z *= constant;
	w += constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Get normalized Vector4
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Vector4<Type>::Normalize(void)
{
	Vector4 result(x, y, z, w);
	Type length = sqrt(x*x + y*y + z*z + w*w);
	result = result / length;
	return result;
}

/******************************************************************************/
/*!
\brief - Get Vector4's length
\return sqrt(x*x + y*y)
*/
/******************************************************************************/
template <typename Type>
Type Vector4<Type>::Length(void) const
{
	return sqrt(x*x + y*y + z*z + w*w);
}