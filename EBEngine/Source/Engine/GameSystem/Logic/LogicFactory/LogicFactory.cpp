/******************************************************************************/
/*!
\file   LogicFactory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains LogicFactory's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "LogicFactory.h"
#include "../LogicBuilder.h"
#include "../../../Utilities/Debug/Debug.h"

//! Init static builder map
LogicBuilderMap LogicFactory::m_builderMap;

/******************************************************************************/
/*!
\brief - Add Builder
\param key - Logic builder key
\param pBuilder - pointer to the builder
*/
/******************************************************************************/
void LogicFactory::AddBuilder(LogicType key, LogicBuilder* pBuilder)
{
	//Find if there is existing stage 
	//If there is, assert
	DEBUG_ASSERT(m_builderMap.find(key) == m_builderMap.end(), "Error: Logic Duplication!");

	//Unless, make new builder
	if (pBuilder)
		m_builderMap.insert(LogicBuilderMap::value_type(key, pBuilder));
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void LogicFactory::ClearBuilderMap(void)
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
\param key - Logic builder key
\param owner - Logic of owner object
*/
/******************************************************************************/
GameLogic* LogicFactory::CreateLogic(Object* owner, LogicType key)
{
	auto bulider = m_builderMap.find(key)->second;
	
	//if there is, return new logic
	if (bulider)
		return bulider->BuildLogic(owner, key);

	return nullptr;
}