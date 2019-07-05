/******************************************************************************/
/*!
\file   Logic.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic's class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _LOGIC_G_
#define _LOGIC_G_

#include <map>
#include "../../../BaseData/Logics/LogicType.h"

class GameLogic;
class ObjectManager;
class GameStateManager;

typedef std::map<int, LogicType> RemoveMap;

//! Logic System class
class Logic
{

public:

	//! Constructor and Destructor
	Logic(ObjectManager* OBM);
	~Logic(void);

	//! Loop functions
	void Load(void);
	void Init(void);
	void Update(float dt);
	void Shutdown(void);
	void Unload(void);

	//! Manage logics
	void RemoveLogic(const int id);
	void RemoveLogic(GameLogic* logic);

private:

	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	RemoveMap m_removeMap;
};

#endif //_LOGIC_G_