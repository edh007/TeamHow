/******************************************************************************/
/*!
\file   GameLogic.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains GameLogic's member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "GameLogic.h"
#include "../../../ObjectManager/Object/Object.h"
#include "../../../ObjectManager/ObjectManager.h"
#include "../../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - ObjectManager Constructor
\param - Logic's original id number
*/
/******************************************************************************/
GameLogic::GameLogic(Object * Owner, LogicType key)
: m_Owner(Owner), m_key(key),
	m_OBM(Owner->GetOBM()), m_GSM(Owner->GetOBM()->GetGSM()),
	m_remove(false), m_OwnerID(m_Owner->GetID())
{}

/******************************************************************************/
/*!
\brief - Get logic's key
\return m_key - Logic's original id number
*/
/******************************************************************************/
LogicType GameLogic::GetKey(void) const
{ 
	return m_key; 
}

/******************************************************************************/
/*!
\brief - Get logic's owner
\return m_Owner - Logic's owner
*/
/******************************************************************************/
Object* GameLogic::GetOwner(void)
{
	return m_Owner;
}

/******************************************************************************/
/*!
\brief - Set remove toggle
\param removeOwner
*/
/******************************************************************************/
void GameLogic::RemoveOwner(bool removeOwner)
{
	m_removeOwner = removeOwner;
	m_Owner->RemoveThis(m_removeOwner);
}

/******************************************************************************/
/*!
\brief - Get remove toggle
\return m_removeOwner
*/
/******************************************************************************/
bool GameLogic::GetRemoveOwner(void) const
{
	return m_removeOwner;
}

/******************************************************************************/
/*!
\brief - Get owner id
\return m_OwnerID
*/
/******************************************************************************/
const int GameLogic::GetOwnerID(void) const
{
	return m_OwnerID;
}

/******************************************************************************/
/*!
\brief - Set remove toggle
\param remove
*/
/******************************************************************************/
void GameLogic::RemoveThis(bool remove)
{
	m_remove = remove;
}

/******************************************************************************/
/*!
\brief - Get remove toggle
\return m_remove
*/
/******************************************************************************/
bool GameLogic::GetRemoveToggle(void) const
{
	return m_remove;
}