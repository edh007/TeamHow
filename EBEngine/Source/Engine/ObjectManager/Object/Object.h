/******************************************************************************/
/*!
\file   Object.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Object's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <unordered_map>
#include "../../../BaseData/Logics/LogicType.h"
#include "../../../BaseData/ArcheTypes/ArcheType.h"
#include "../../../BaseData/Components/ComponentType.h"

class Component;
class GameLogic;
class ObjectManager;

typedef std::unordered_map<LogicType, GameLogic*> LogicMap;
typedef std::unordered_map<ComponentType, Component*> ComponentMap;

//! Basic Object class
class Object {

public:

	Object(ArcheType type, ObjectManager* OBM = 0);
	~Object();

	// Id functions
	const int GetID(void) const;
	ArcheType GetArcheType(void) const;

	// Set dt offset
	void SetdtOffset(float offset);
	float GetdtOffset(void) const;

	ObjectManager* GetOBM(void) const;
	void RemoveThis(bool toggle);
	bool GetRemoveToggle(void) const;

	// GameLogic function
	void AddLogic(GameLogic* logic);
	void ClearLogicList(void);
	LogicMap& GetLogicList(void);
	bool HasLogic(LogicType type);
	void RemoveLogic(LogicType type);

	/******************************************************************************/
	/*!
	\brief - Get specific logic
	*/
	/******************************************************************************/
	template <class Type>
	Type* GetLogic(LogicType key)
	{
		auto found = m_logicList.find(key);
		if (found != m_logicList.end())
			return static_cast<Type*>(found->second);

		return nullptr;
	}

	// Component functions
	void AddComponent(Component* component);
	void ClearComponentList(void);
	ComponentMap& GetComponentList(void);
	bool HasComponent(ComponentType type);
	void RemoveComponent(ComponentType type);

	/******************************************************************************/
	/*!
	\brief - Get specific component
	*/
	/******************************************************************************/
	template <class Type>
	Type* GetComponent(ComponentType key)
	{
		auto found = m_componentList.find(key);
		if (found != m_componentList.end())
			return static_cast<Type*>(found->second);

		return nullptr;
	}

private:

	ArcheType m_atType;		//! ArcheType;
	int m_id;				//! Object id
	bool m_remove;			//! Remove toggle

protected:

	float m_dtOffset;				//! Manipulate dt
	ObjectManager* m_OBM;			//! Pointer to object manager
	LogicMap m_logicList;			//! Logic list
	ComponentMap m_componentList;	//! Component list
};

#endif // _OBJECT_H_