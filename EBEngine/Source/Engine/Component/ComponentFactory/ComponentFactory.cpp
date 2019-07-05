/******************************************************************************/
/*!
\file   ComponentFactory.cpp
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
	Contains ComponentFactory's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ComponentFactory.h"
#include "../ComponentBuilder.h"
#include "../../Utilities/Debug/Debug.h"

//! Init component build map
ComponentBuilderMap ComponentFactory::m_builderMap;

/******************************************************************************/
/*!
\brief - Add Builder
\param key - Component builder key
\param pBuilder - pointer to the builder
*/
/******************************************************************************/
void ComponentFactory::AddBuilder(ComponentType key, ComponentBuilder* pBuilder)
{
	//Find if there is existing stage 
	//If there is, assert
	DEBUG_ASSERT(m_builderMap.find(key) == m_builderMap.end(), "Error: Component Duplication!");

	//Unless, make new builder
	if (pBuilder)
		m_builderMap.insert(ComponentBuilderMap::value_type(key, pBuilder));
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void ComponentFactory::ClearBuilderMap(void)
{
	for (auto it = m_builderMap.begin(); it != m_builderMap.end(); ++it)
	{
		delete it->second;
		it->second = 0;
	}

	m_builderMap.clear();
}

/******************************************************************************/
/*!
\brief - Create stage
\param key - Component builder key
\param owner - Component of owner object
*/
/******************************************************************************/
Component* ComponentFactory::CreateComponent(Object* Owner, ComponentType key)
{
	auto bulider = m_builderMap.find(key)->second;

	//if there is, return new logic
	if (bulider)
		return bulider->BuildComponent(Owner, key);

	return nullptr;
}
