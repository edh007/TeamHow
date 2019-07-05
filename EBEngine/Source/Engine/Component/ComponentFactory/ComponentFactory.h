/******************************************************************************/
/*!
\file   ComponentFactory.h
\author Jeong.Juyong
\par    email: jeykop14@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
	Contains component builder's info

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _COMPONENTFACTORY_H_
#define _COMPONENTFACTORY_H_

#include <map>
#include "../../../BaseData/Components/ComponentType.h"

class Object;
class Component;
class ComponentBuilder;

typedef std::map <ComponentType, ComponentBuilder*> ComponentBuilderMap;

//! Component Factoty class
class ComponentFactory
{

public:

	//! Destructor
	~ComponentFactory(void) {};

	//! Function manages Component
	static void AddBuilder(ComponentType key, ComponentBuilder* pBuilder);
	static void ClearBuilderMap(void);

	//! Create Component
	static Component* CreateComponent(Object *owner, ComponentType key);

private:

	static ComponentBuilderMap m_builderMap;

};

#endif //_COMPONENTFACTORY_H_