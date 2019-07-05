/******************************************************************************/
/*!
\file   Vector2.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Vector2's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Vector2.h"
#include "Vector3.h"

/******************************************************************************/
/*!
\brief - Vector2 Destructor
*/
/******************************************************************************/
Vector2::~Vector2(void)
{}

/******************************************************************************/
/*!
\brief - Vector2 Constructor
\param _x - element x
\param _y - element y
*/
/******************************************************************************/
Vector2::Vector2(float _x, float _y)
:x(_x), y(_y)
{}

/******************************************************************************/
/*!
\brief - Vector2 Copy Constructor
\param copy - vector2 to be copied
*/
/******************************************************************************/
Vector2::Vector2(const Vector3<float>& copy)
	: x (copy.x), y (copy.y)
{}

/******************************************************************************/
/*!
\brief - Vector2 Copy Constructor
\param copy - vector2 to be copied
*/
/******************************************************************************/
Vector2::Vector2(const Vector2& copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
	}
}

/******************************************************************************/
/*!
\brief - Vector2 < operator
\param rhs - vector2 to be compared
\return bool
*/
/******************************************************************************/
bool Vector2::operator<(const Vector2 & rhs) const
{
	return this->Length() < rhs.Length();
}

/******************************************************************************/
/*!
\brief - Vector2 == operator
\param rhs - vector2 to be compared
\return bool
*/
/******************************************************************************/
bool Vector2::operator==(const Vector2 & rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

/******************************************************************************/
/*!
\brief - Vector2 != operator
\param rhs - vector2 to be compared
\return bool
*/
/******************************************************************************/
bool Vector2::operator!=(const Vector2 & rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

/******************************************************************************/
/*!
\brief - Vector2 = operator
\param rhs - vector2 to be assigned
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator=(const Vector2& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 unary - operator
\param rhs - vector2 to be assigned
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator-(void)
{
	x = -x;
	y = -y;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 += operator
\param rhs - vector2 to be added
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 += operator
\param rhs - number to be added
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator+=(const float constant)
{
	x += constant;
	y += constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 -= operator
\param rhs - vector2 to be subtracted
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 -= operator
\param rhs - number to be subtracted
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator-=(const float constant)
{
	x -= constant;
	y -= constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 *= operator
\param rhs - vector2 to be multiplied
\return *this
*/
/******************************************************************************/
Vector2& Vector2::operator*=(const float constant)
{
	x *= constant;
	y *= constant;

	return *this;
}

/******************************************************************************/
/*!
\brief - Vector2 + operator
\param rhs - number to be added
\return new_one
*/
/******************************************************************************/
Vector2 Vector2::operator+(const float constant) const
{
	Vector2 new_one;

	new_one.x = x + constant;
	new_one.y = y + constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector2 + operator
\param rhs - vector2 to be added
\return new_one
*/
/******************************************************************************/
Vector2 Vector2::operator+(const Vector2& rhs) const
{
	Vector2 new_one;

	new_one.x = x + rhs.x;
	new_one.y = y + rhs.y;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector2 - operator
\param rhs - number to be subtracted
\return new_one
*/
/******************************************************************************/
Vector2 Vector2::operator-(const float constant) const
{
	Vector2 new_one;

	new_one.x = x - constant;
	new_one.y = y - constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector2 - operator
\param rhs - vector2 to be subtracted
\return new_one
*/
/******************************************************************************/
Vector2 Vector2::operator-(const Vector2& rhs) const
{
	Vector2 new_one;

	new_one.x = x - rhs.x;
	new_one.y = y - rhs.y;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector2 * operator
\param rhs - number to be nultiplied
\return new_one
*/
/******************************************************************************/
Vector2 Vector2::operator*(const float constant) const
{
	Vector2 new_one;

	new_one.x = x * constant;
	new_one.y = y * constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Vector2 / operator
\param rhs - number to be divided
\return new_one
*/
/******************************************************************************/
Vector2 Vector2::operator/(const float constant) const
{
	Vector2 new_one;

	new_one.x = x / constant;
	new_one.y = y / constant;

	return new_one;
}

/******************************************************************************/
/*!
\brief - Get Vector2's length
\return sqrt(x*x + y*y)
*/
/******************************************************************************/
float Vector2::Length(void) const
{
	return sqrt(x*x + y*y);
}

/******************************************************************************/
/*!
\brief - Get two Vector2s' DotProduct
\param rhs - to be calculated
\return x * rhs.x + y * rhs.y;
*/
/******************************************************************************/
float Vector2::DotProduct(const Vector2& rhs)
{
	return x * rhs.x + y * rhs.y;
}

/******************************************************************************/
/*!
\brief - Get two Vector2s' CrossProduct
\param rhs - to be calculated
\return x * x * rhs.y - y * rhs.x;
*/
/******************************************************************************/
Vector2 Vector2::CrossProduct(const Vector2& rhs)
{
	return x * rhs.y - y * rhs.x;
}

/******************************************************************************/
/*!
\brief - Get normalized vector2
\return result
*/
/******************************************************************************/
Vector2 Vector2::Normalize(void)
{
	Vector2 result(x, y);
	result = result / Length();
	return result;
}


/******************************************************************************/
/*!
\brief - Friend function, + operator
\param constant - number to be added 
\param rhs - *this
\return new_one
*/
/******************************************************************************/
Vector2 operator+(float constant, const Vector2& rhs)
{
	Vector2 new_one;

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
Vector2 operator*(float constant, const Vector2& rhs)
{
	Vector2 new_one;

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
std::ostream& operator<<(std::ostream& os, const Vector2& constents)
{
	os << "Vector2[ " << constents.x << ", " << constents.y << " ]";
	return os;
}