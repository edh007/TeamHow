/******************************************************************************/
/*!
\file   LogicBuilder.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic builder's class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _LOGICBUILDER_H_
#define _LOGICBUILDER_H_

#include "GameLogic/GameLogic.h"

//! Virtual logic builder class
class LogicBuilder{

public:

	//! Basic constructor and destructor,
	//! build function
	LogicBuilder() {};
	virtual ~LogicBuilder(void) {};
	virtual GameLogic* BuildLogic(Object* Owner, LogicType key) const = 0;

private:

};

#endif //_LOGICBUILDER_H_