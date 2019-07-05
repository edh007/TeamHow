/******************************************************************************/
/*!
\file   Factory.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Factory's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <map>
#include "../../../BaseData/Stages/StageType.h"

class Stage;
class StageBuilder;
class ObjectManager;
class GameStateManager;

typedef std::map<StageType, StageBuilder*> StageBuilderMap;

//! class Factory
class StageFactory
{

public:

	//! Destructor
	~StageFactory(void);

	//! Function manages factory
	static void AddBuilder(StageType stage, StageBuilder* pBuilder);
	static void ClearBuilderMap(void);

	//! Create stage
	static Stage* CreateStage(StageType stage, GameStateManager* GSM, ObjectManager* OBM);

private:

	//! Builder list
	static StageBuilderMap m_builderMap;

};

#endif // FACTORY_H_