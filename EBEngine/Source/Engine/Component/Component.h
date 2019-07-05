/******************************************************************************/
/*!
\file   Component.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
Contains virtual component info 

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../../BaseData/Components/ComponentType.h"

class Object;
class ObjectManager;
class GameStateManager;

//! Virtual component class
class Component {

public:

	Component(Object* Owner, ComponentType key);
	virtual ~Component(void);

	ComponentType GetKey(void) const;
	Object* GetOwner(void);

protected:

	//int OwnerID;
	Object* m_Owner;
	ComponentType m_key;
};

#endif // _COMPONENT_H_