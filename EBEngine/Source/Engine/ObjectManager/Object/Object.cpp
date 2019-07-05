/******************************************************************************/
/*!
\file   Object.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Object's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Object.h"
#include "../ObjectManager.h"
#include "../../Component/Component.h"
#include "../../GameSystem/Logic/Logic.h"
#include "../../GameSystem/Logic/GameLogic/GameLogic.h"
#include "../../GameSystem/Logic/LogicFactory/LogicFactory.h"

/******************************************************************************/
/*!
\brief - Object's constructor
\param id - Object's id
\param type - Object's type
\param OBM - Pointer to object manager
*/
/******************************************************************************/
Object::Object(ArcheType type, ObjectManager* OBM)
: m_atType(type), m_OBM(OBM), m_id(OBM->GetNextID()), 
m_remove(true), m_dtOffset(1.f)
{}

/******************************************************************************/
/*!
\brief - Object's Destructor
*/
/******************************************************************************/
Object::~Object()
{
	// Clear all logics and components
 	ClearLogicList();
	ClearComponentList();
}

/******************************************************************************/
/*!
\brief - Get Object's id
\return m_id - Object's id
*/
/******************************************************************************/
const int Object::GetID(void) const
{
	return m_id;
}

/******************************************************************************/
/*!
\brief - Add a logic to object's list
\param logic_name - logic's name
*/
/******************************************************************************/
void Object::AddLogic(GameLogic* logic)
{
	// Remove exsting logic
	auto found = m_logicList.find(logic->GetKey());
	if (found != m_logicList.end())
	{
		delete found->second;
		m_logicList.erase(found);
	}

	// Add logic to the object's logic list
	m_logicList.insert(LogicMap::value_type(
		logic->GetKey(), logic));
}

/******************************************************************************/
/*!
\brief - Get the object's logic list
\return m_logicList
*/
/******************************************************************************/
LogicMap& Object::GetLogicList(void)
{
	return m_logicList;
}

/******************************************************************************/
/*!
\brief - Get pointer to the OBM
\return m_OBM
*/
/******************************************************************************/
ObjectManager* Object::GetOBM(void) const
{
	return m_OBM;
}

/******************************************************************************/
/*!
\brief - Get object's ArcheType
\return m_atType
*/
/******************************************************************************/
ArcheType Object::GetArcheType(void) const
{
	return m_atType;
}

/******************************************************************************/
/*!
\brief -  Manipulate dt offset
\param offset
*/
/******************************************************************************/
void Object::SetdtOffset(float offset)
{
	m_dtOffset = offset;
}

/******************************************************************************/
/*!
\brief - Get dt offset
\return m_dtOffset
*/
/******************************************************************************/
float Object::GetdtOffset(void) const
{
	return m_dtOffset;
}

/******************************************************************************/
/*!
\brief - Check if there is specific logic
*/
/******************************************************************************/
bool Object::HasLogic(LogicType type)
{
	auto found = m_logicList.find(type);
	if (found != m_logicList.end())
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Delete specific logic
\param type - logic key type
*/
/******************************************************************************/
void Object::RemoveLogic(LogicType type)
{
	auto found = m_logicList.find(type);
	if (found != m_logicList.end())
	{
		found->second->Shutdown();
		found->second->Unload();

		delete found->second;
		found->second = 0;
		m_logicList.erase(found);
	}
}

/******************************************************************************/
/*!
\brief - Clear all logics in the list
*/
/******************************************************************************/
void Object::ClearLogicList(void)
{
	for (auto it = m_logicList.begin(); it != m_logicList.end(); )
	{
		(*it).second->Shutdown();
		(*it).second->Unload();
		delete (*it++).second;
	}

	m_logicList.clear();
}

/******************************************************************************/
/*!
\brief - Decide this object to remove or not
\param toggle
*/
/******************************************************************************/
void Object::RemoveThis(bool toggle)
{
	m_remove = toggle;
}

/******************************************************************************/
/*!
\brief - Delete specific logic
\return m_remove
*/
/******************************************************************************/
bool Object::GetRemoveToggle(void) const
{
	return m_remove;
}

/******************************************************************************/
/*!
\brief - Clear all components in the list
*/
/******************************************************************************/
void Object::ClearComponentList(void)
{
	for (auto it = m_componentList.begin(); it != m_componentList.end(); )
		delete (*it++).second;

	m_componentList.clear();
}

/******************************************************************************/
/*!
\brief - Add a component to object's list
\param component
*/
/******************************************************************************/
void Object::AddComponent(Component* component)
{
	// Remove exsting component
	auto found = m_componentList.find(component->GetKey());
	if (found != m_componentList.end())
	{
		delete found->second;
		m_componentList.erase(found);
	}

	// Add logic to the object's logic list
	m_componentList.insert(ComponentMap::value_type(
		component->GetKey(), component));
}

/******************************************************************************/
/*!
\brief - Get the object's component list
\return m_logicList
*/
/******************************************************************************/
ComponentMap& Object::GetComponentList(void)
{
	return m_componentList;
}

/******************************************************************************/
/*!
\brief - Check if there is specific component
*/
/******************************************************************************/
bool Object::HasComponent(ComponentType type)
{
	auto found = m_componentList.find(type);
	if (found != m_componentList.end())
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Delete specific component
*/
/******************************************************************************/
void Object::RemoveComponent(ComponentType type)
{
	auto found = m_componentList.find(type);
	if (found != m_componentList.end())
	{
		delete found->second;
		found->second = 0;
		m_componentList.erase(found);
	}
}
