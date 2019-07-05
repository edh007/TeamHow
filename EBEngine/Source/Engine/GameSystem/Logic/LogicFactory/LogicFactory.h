/******************************************************************************/
/*!
\file   LogicFactory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains LogicFactory class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _LOGICFACTORY_H_
#define _LOGICFACTORY_H_

#include <map>
#include "../../../../BaseData/Logics/LogicType.h"

class Object;
class GameLogic;
class LogicBuilder;

typedef std::map <LogicType, LogicBuilder*> LogicBuilderMap;

//! Logic Factoty class
class LogicFactory
{

public:

	//! Destructor
	~LogicFactory(void) {};

	//! Function manages logic
	static void AddBuilder(LogicType key, LogicBuilder* pBuilder);
	static void ClearBuilderMap(void);

	//! Create logic
	static GameLogic* CreateLogic(Object *owner, LogicType key);

private:

	static LogicBuilderMap m_builderMap;

};

#endif // _LOGICFACTORY_H_