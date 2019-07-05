/******************************************************************************/
/*!
\file   Factory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Factory's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "StageFactory.h"
#include "../StageBuilder.h"
#include "../../Utilities/Debug/Debug.h"

//! Init static builder map
StageBuilderMap StageFactory::m_builderMap;

/******************************************************************************/
/*!
\brief - Factory Destrutor
*/
/******************************************************************************/
StageFactory::~StageFactory(void)
{}

/******************************************************************************/
/*!
\brief - Add Builder
\param stage - stage to make
\param pBuilder - pointer to the builder
*/
/******************************************************************************/
void StageFactory::AddBuilder(StageType stage, StageBuilder* pBuilder)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);
	
	//If there is, assert
	DEBUG_ASSERT(found == m_builderMap.end(), "Error: Stage Duplication!");

	//Unless, make new builder
	m_builderMap.insert(std::make_pair(stage, pBuilder));
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void StageFactory::ClearBuilderMap()
{
	for (auto it = m_builderMap.begin(); it != m_builderMap.end(); ++it)
		delete it->second;

	m_builderMap.clear();
}

/******************************************************************************/
/*!
\brief - Create stage
\param stage - stage to make
\param GSM - GSM to puint to the stage
*/
/******************************************************************************/
Stage* StageFactory::CreateStage(StageType stage, GameStateManager* GSM, ObjectManager* OBM)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);

	//if there is, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Existing Stage!");

	//If there is make
	return found->second->BuildStage(GSM, OBM);
}