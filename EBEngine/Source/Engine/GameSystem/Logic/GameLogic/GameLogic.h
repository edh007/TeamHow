/******************************************************************************/
/*!
\file   GameLogic.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains GameLogic's virtual class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "json/json.h"
#include "../../../../BaseData/Logics/LogicType.h"

class Object;
class Sprite;
class ObjectManager;
class GameStateManager;

//! Virtual GameLogic class
class GameLogic
{
public:

	// Constructor and Destructor
	GameLogic(Object* Owner = 0, LogicType key = NONE_LOGIC);
	virtual ~GameLogic(void) {};

	// Virtual basic functions
	virtual void Load(const Json::Value& data) = 0;
	virtual void Init(void) = 0;
	virtual void Update(float dt) = 0;
	virtual void Shutdown(void) = 0;
	virtual void Unload(void) = 0;

	LogicType GetKey(void) const;
	Object* GetOwner(void);

	//! Manage logic's existance
	void RemoveThis(bool remove);
	bool GetRemoveToggle(void) const;

	//! Manage owner's existance
	void RemoveOwner(bool removeOwner);
	bool GetRemoveOwner(void) const;

	const int GetOwnerID(void) const;

protected:

	bool m_remove;
	bool m_removeOwner;
	LogicType m_key;

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	int m_OwnerID;

private:

};

#endif // _GAMELOGIC_H_