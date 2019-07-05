/******************************************************************************/
/*!
\file   Logic.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Logic.h"
#include "GameLogic/GameLogic.h"
#include "../../ObjectManager/Object/Object.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Logic Constructor
*/
/******************************************************************************/
Logic::Logic(ObjectManager* OBM)
	: m_OBM(OBM), m_GSM(m_OBM->GetGSM())
{}

/******************************************************************************/
/*!
\brief - Logic Destrutor
*/
/******************************************************************************/
Logic::~Logic(void)
{}

/******************************************************************************/
/*!
\brief - Logic Load function
*/
/******************************************************************************/
void Logic::Load(void)
{
	// They load when they're loaded from the data files
}

/******************************************************************************/
/*!
\brief - Logic Init function
\param gd - Game data
*/
/******************************************************************************/
void Logic::Init(void)
{
	// They init when they're added to obj list
}

/******************************************************************************/
/*!
\brief - Logic Update function
\param dt - delta time
*/
/******************************************************************************/
void Logic::Update(float dt)
{
	// Update objects' logics
	for (auto obj = m_OBM->GetObjectMap().begin();
		obj != m_OBM->GetObjectMap().end(); ++obj)
	{
		// Update logics
		for (auto logic = obj->second->GetLogicList().begin();
			logic != obj->second->GetLogicList().end(); ++logic)
		{
			// Logic to be deleted
			// or Owner to be deleted
			if (logic->second->GetRemoveToggle()
				|| logic->second->GetRemoveOwner())
			{
				// Shutdown the game logic
				logic->second->Shutdown();

				// Store object to remove
				if (logic->second->GetRemoveOwner()) {
					m_OBM->RemoveObject(obj->second->GetID());
					break;
				}

				// Store logic to remove
				else
					m_removeMap.insert(RemoveMap::value_type(
						logic->second->GetOwnerID(), logic->second->GetKey()));
			}

			// Nothing happened
			else
				logic->second->Update(dt);
		}
	}

	// Removing process after update
	if (m_removeMap.size())
	for (auto it = m_removeMap.begin();
		it != m_removeMap.end(); ++it)
	{
		int id = it->second;									// Get obj id
		auto found = m_removeMap.find(id);						// Get logic type
		
		if (found != m_removeMap.end())
			m_OBM->GetGameObject(id)->RemoveLogic(found->second);	// Remove logic
	}
}

/******************************************************************************/
/*!
\brief - Logic Shutdown function
\param gd - Game data
*/
/******************************************************************************/
void Logic::Shutdown(void)
{
	for (auto obj = m_OBM->GetObjectMap().begin();
		obj != m_OBM->GetObjectMap().end(); ++obj)
	{
		for (auto logic = obj->second->GetLogicList().begin();
			logic != obj->second->GetLogicList().end(); ++logic)
			logic->second->Shutdown();
	}
}

/******************************************************************************/
/*!
\brief - Logic Unload function
*/
/******************************************************************************/
void Logic::Unload()
{
	for (auto obj = m_OBM->GetObjectMap().begin();
		obj != m_OBM->GetObjectMap().end(); ++obj)
	{
		for (auto logic = obj->second->GetLogicList().begin();
			logic != obj->second->GetLogicList().end(); ++logic)
			logic->second->Unload();
	}
}

/******************************************************************************/
/*!
\brief - Remove the object's all logics from the logiclist
\param - id
*/
/******************************************************************************/
void Logic::RemoveLogic(const int id)
{
	// Find the object
	auto found = m_OBM->GetObjectMap().find(id);

	found->second->ClearLogicList();
}

/******************************************************************************/
/*!
\brief - Remove the object's one logic from the logiclist
\param - logic
*/
/******************************************************************************/
void Logic::RemoveLogic(GameLogic* logic)
{
	// Find the object
	auto found = m_OBM->GetObjectMap().find(logic->GetOwnerID());
	
	// Remove the logic of that object
	found->second->RemoveLogic(logic->GetKey());
}