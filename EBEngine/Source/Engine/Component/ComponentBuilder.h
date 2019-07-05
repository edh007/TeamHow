/******************************************************************************/
/*!
\file   ComponentBuilder.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/12/20(yy/mm/dd)

\description
Contains component builder's class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _COMPONENTBUILDER_H_
#define _COMPONENTBUILDER_H_

#include "Component.h"

//! Virtual componnet builder class
class ComponentBuilder {

public:

	//! Basic constructor and destructor,
	//! build function
	ComponentBuilder() {};
	virtual ~ComponentBuilder(void) {};
	virtual Component* BuildComponent(Object* Owner, ComponentType key) const = 0;

private:

};

#endif //_COMPONENTBUILDER_H_