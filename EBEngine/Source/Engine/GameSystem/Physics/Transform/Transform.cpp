/******************************************************************************/
/*!
\file   Transform.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
Contains Transform component's member functions body info

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Transform.h"

/******************************************************************************/
/*!
\brief - TransformBuilder constructor
\param Owner - Owner of this Component
\param key - ComponentType
\return new Transform
*/
/******************************************************************************/
Component* TransformBuilder::BuildComponent(Object* Owner, ComponentType key) const {
	return new Transform(Owner, key);
};

/******************************************************************************/
/*!
\brief - Transform constructor
\param Owner - Owner of this Component
\param key - ComponentType
*/
/******************************************************************************/
Transform::Transform(Object* Owner, ComponentType key)
	:Component(Owner, key), 
	m_position(vec3()), m_scale(vec3()), m_rotation(0.f)
{}

/******************************************************************************/
/*!
\brief - Set position
\param position 
*/
/******************************************************************************/
void Transform::SetPosition(const vec3& position)
{
	m_position = position;
}

/******************************************************************************/
/*!
\brief - Set scale
\param scale
*/
/******************************************************************************/
void Transform::SetScale(const vec3& scale)
{
	m_scale = scale;
}

/******************************************************************************/
/*!
\brief - Get position
\return m_position
*/
/******************************************************************************/
vec3 Transform::GetPosition(void) const
{
	return m_position;
}

/******************************************************************************/
/*!
\brief - Get scale
\return scale
*/
/******************************************************************************/
vec3 Transform::GetScale(void) const
{
	return m_scale;
}

/******************************************************************************/
/*!
\brief - Set rotation
\param rotation
*/
/******************************************************************************/
void Transform::SetRotation(float rotation)
{
	m_rotation = rotation;
	
	// Lock meaningless values
	if (m_rotation > 360) m_rotation -= 360.f;
	else if (m_rotation < 0) m_rotation = 360.f + m_rotation;
}

/******************************************************************************/
/*!
\brief - Get rotation
\return m_rotation
*/
/******************************************************************************/
float Transform::GetRotation(void) const
{
	return m_rotation;
}