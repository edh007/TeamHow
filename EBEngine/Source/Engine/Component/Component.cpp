/******************************************************************************/
/*!
\file   Component.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
Contains virtual component's member functions' body

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Component.h"

/******************************************************************************/
/*!
\brief - Component constructor
\param Owner - Owner of this Component
\param key - ComponentType
*/
/******************************************************************************/
Component::Component(Object * Owner, ComponentType key)
	: m_Owner(Owner), m_key(key)
{}

/******************************************************************************/
/*!
\brief - Component destructor
*/
/******************************************************************************/
Component::~Component(void)
{}

/******************************************************************************/
/*!
\brief - Get component type
\return m_key
*/
/******************************************************************************/
ComponentType Component::GetKey(void) const
{
	return m_key;
}

/******************************************************************************/
/*!
\brief - Get component's owner
\return m_key
*/
/******************************************************************************/
Object* Component::GetOwner(void)
{
	return m_Owner;
}
