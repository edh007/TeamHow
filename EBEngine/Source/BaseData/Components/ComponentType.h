/******************************************************************************/
/*!
\file   ComponentType.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
	Contains header files(ComponentType) to provide users base engine

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _COMPONENTTPYE_H_
#define _COMPONENTTPYE_H_

#include <string>

enum ComponentType {

	CT_NONE,

	CT_TRANSFORM,
	CT_RIGIDBODY,
	CT_SPRITE,
	CT_TEXT,
	CT_PARTICLE,

	CT_END
};

/******************************************************************************/
/*!
\brief - Convert sring key to enum(ComponentType).
*/
/******************************************************************************/
inline ComponentType ComponentTypeConverter(const std::string& key)
{
	// Define components

	if (key == "TRANSFORM")
		return CT_TRANSFORM;
	else if (key == "RIGIDBODY")
		return CT_RIGIDBODY;
	else if (key == "SPRITE")
		return CT_SPRITE;
	else if (key == "TEXT")
		return CT_TEXT;
	else if (key == "PARTICLE")
		return CT_PARTICLE;
	else
		return CT_NONE;
}

#endif //_COMPONENTTPYE_H_
