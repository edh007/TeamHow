/******************************************************************************/
/*!
\file   Vector3.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains vector3's template class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Vector2.h"
#include "Vector4.h"
#include <cmath>
#include "Vector3.h"

/******************************************************************************/
/*!
\brief - Vector3 Destructor
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>::~Vector3(void)
{}

/******************************************************************************/
/*!
\brief - Vector3 Constructor
\param _x - element x
\param _y - element y
\param _z - element z
*/
/******************************************************************************/
template<typename Type>
Vector3<Type>::Vector3(Type _x, Type _y, Type _z)
: x(_x), y(_y), z(_z)
{}

/******************************************************************************/
/*!
\brief - Vector3 Copy Constructor
\param copy - Vector2 to be copied
*/
/******************************************************************************/
template<typename Type>
Vector3<Type>::Vector3(const Vector2& copy, Type _z = 0)
	:x(copy.x), y(copy.y), z(_z)
{}

/******************************************************************************/
/*!
\brief - Vector3 Copy Constructor
\param copy - Vector3 to be copied
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>::Vector3(const Vector3<Type>& copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}
}

/******************************************************************************/
/*!
\brief - Vecto4 converter
\param copy - to be converted to vector3
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>::Vector3(const Vector4<Type>& copy)
	:x(copy.x), y(copy.y), z(copy.z)
{}

/******************************************************************************/
/*!
\brief - Vector3 = operator
\param rhs - vector3 to be assigned
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator=(const Vector3& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector3 unary - operator
\param rhs - Vector3 to be assigned
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator-(void)
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector3 + operator
\param rhs - number to be added
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::operator+(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x + constant;
	new_one.y = y + constant;
	new_one.z = z + constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector3 + operator
\param rhs - Vector3 to be added
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::operator+(const Vector3& rhs) const
{
	Vector3 new_one;

	new_one.x = x + rhs.x;
	new_one.y = y + rhs.y;
	new_one.z = z + rhs.z;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector3 - operator
\param rhs - number to be subtracted
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::operator-(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x - constant;
	new_one.y = y - constant;
	new_one.z = z - constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector3 - operator
\param rhs - Vector3 to be subtracted
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::operator-(const Vector3& rhs) const
{
	Vector3 new_one;

	new_one.x = x - rhs.x;
	new_one.y = y - rhs.y;
	new_one.z = z - rhs.z;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector3 * operator
\param rhs - number to be nultiplied
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::operator*(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x * constant;
	new_one.y = y * constant;
	new_one.z = z * constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector3 / operator
\param rhs - number to be divided
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::operator/(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x / constant;
	new_one.y = y / constant;
	new_one.z = z / constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Friend function, + operator
\param constant - number to be added
\param rhs - *this
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> operator+(Type constant, const Vector3<Type>& rhs)
{
	Vector3<Type> new_one;

	new_one = rhs + constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Friend function, * operator
\param constant - number to be multiplied
\param rhs - *this
\return new_one
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> operator*(Type constant, const Vector3<Type>& rhs)
{
	Vector3<Type> new_one;

	new_one = rhs * constant;

	return new_one;
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
std::ostream& operator<<(std::ostream& os, const Vector3<Type>& contents)
{
	os << "Vector3[ " << contents.x << ", " << contents.y << ", " << contents.z << " ]";
	return os;
}

/******************************************************************************/
/*!
\brief - Get two vector3s' DotProduct
\param rhs - to be calculated
\return x * rhs.x + y * rhs.y;
*/
/******************************************************************************/
template <typename Type>
Type Vector3<Type>::DotProduct(const Vector3& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

/******************************************************************************/
/*!
\brief - Get two vector3s' CrossProduct
\param rhs - to be calculated
\return x * x * rhs.y - y * rhs.x;
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::CrossProduct(const Vector3& rhs)
{
	Vector3 result;

	result.x = y * rhs.z - z * rhs.y;
	result.y = z * rhs.x - x * rhs.z;
	result.z = x * rhs.y - y * rhs.x;

	return result;
}

/******************************************************************************/
/*!
\brief - Vector3 += operator
\param rhs - Vector3 to be added
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector3 += operator
\param rhs - number to be added
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator+=(const Type& constant)
{
	x += constant;
	y += constant;
	z += constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector3 -= operator
\param rhs - Vector3 to be subtracted
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector3 -= operator
\param rhs - number to be subtracted
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator-=(const Type& constant)
{
	x -= constant;
	y -= constant;
	z -= constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector3 *= operator
\param rhs - Vector3 to be multiplied
\return *this
*/
/******************************************************************************/
template <typename Type>
Vector3<Type>& Vector3<Type>::operator*=(const Type& constant)
{
	x *= constant;
	y *= constant;
	z *= constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Get normalized vector3
\return result
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::Normalize(void)
{
	
		Vector3 result(x, y, z);

		//try {
			if (!Length())
				return vec3();//throw this;
		//}

		//catch (Vector3<Type> exception) {
		//	std::cout << "Cannot calculate properly...\n";
		//}

		result = result / Length();
		return result;
	
}

/******************************************************************************/
/*!
\brief - Get vector3's length
\return sqrt(x*x + y*y)
*/
/******************************************************************************/
template <typename Type>
Type Vector3<Type>::Length(void) const
{
	return sqrt(x*x + y*y + z*z);
}

/******************************************************************************/
/*!
\brief - Calculate vector's absolute value
\return result
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::Absolute(void)
{
	Vector3 result(x, y, z);

	if (result.x < 0)
		result.x = -result.x;
	if (result.y < 0)
		result.y = -result.y;
	if (result.z < 0)
		result.z = -result.z;

	return result;
}

/******************************************************************************/
/*!
\brief - Calculate vector's rotated position; Regard vector as a point
\param angle - degree to rotate
\param pivot - pivot point
\return point
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::Rotation(float angle, const Vector3& pivot)
{
	Vector3 point(*this);

	float s = sinf(Math::DegToRad(angle));
	float c = cosf(Math::DegToRad(angle));

	point.x -= pivot.x;
	point.y -= pivot.y;

	float new_x = point.x * c - point.y * s;
	float new_y = point.x * s + point.y * c;

	point.x = new_x + pivot.x;
	point.y = new_y + pivot.y;

	return point;
}

/******************************************************************************/
/*!
\brief - Calculate vector's reflection
\param rhs - vector to reflect
\return reflected
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::Reflection(Vector3 rhs)
{
	Vector3 reflected;
	Vector3 norm = rhs.Normalize();
	
	reflected = (*this) - 2 * ((*this).DotProduct(norm)) * norm;

	return reflected;
}

/******************************************************************************/
/*!
\brief - Calculate 2 vectors' included angle
\param other - 2nd vector
\return Math::RadToDeg(radian)
*/
/******************************************************************************/
template <typename Type>
float Vector3<Type>::IncludedAngle(const Vector3& other)
{
	float radian = atan2(x * other.y - other.x * y, *this.DotProduct(b));

	return Math::RadToDeg(radian);
}

/******************************************************************************/
/*!
\brief - Calculate rotated vector
\param angle - degree to rotate
\return result
*/
/******************************************************************************/
template <typename Type>
Vector3<Type> Vector3<Type>::Rotation(float angle)
{
	Vector3 result;

	result.x = x * cosf(Math::DegToRad(angle)) - y * sinf(Math::DegToRad(angle));
	result.y = x * sinf(Math::DegToRad(angle)) + y * cosf(Math::DegToRad(angle));

	return result;
}

/******************************************************************************/
/*!
\brief - Compare == operator
\param rhs - to be compared
\return bool
*/
/******************************************************************************/
template<typename Type>
bool Vector3<Type>::operator==(const Vector3& rhs)
{
	if (x != rhs.x || y != rhs.y || z != rhs.z)
		return false;

	return true;
}

/******************************************************************************/
/*!
\brief - Compare != operator
\param rhs - to be compared
\return bool
*/
/******************************************************************************/
template<typename Type>
bool Vector3<Type>::operator!=(const Vector3& rhs)
{
	if (x != rhs.x || y != rhs.y || z != rhs.z)
		return true;

	return false;
}

