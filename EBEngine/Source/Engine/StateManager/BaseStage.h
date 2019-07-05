/******************************************************************************/
/*!
\file   BaseStage.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains base stage, base utils' header files consists of stage(state)

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _BASESTAGE_H_
#define _BASESTAGE_H_

#include "../Utilities/Time.h"

class Scene;
class World;
class Sprite;
class ObjectManager; 
class GameStateManager;

//! Virtual stage class
class Stage
{
public:

	Stage(GameStateManager* GSM = 0, ObjectManager* OBM = 0)
	{
		m_GSM = GSM;
		m_OBM = OBM;
	};

	virtual ~Stage() {};
	virtual void Load() = 0;
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Shutdown() = 0;
	virtual void Unload() = 0;

	/******************************************************************************/
	/*!
	\brief - Get elapsed time
	\return m_time.GetElapsedTime() 
	*/
	/******************************************************************************/
	float GetTimerElapsed(void) {
		return m_time.GetElapsedTime();
	};

	ObjectManager* m_OBM;
	GameStateManager* m_GSM;
	Timer m_time;
};

#endif //_BASESTAGE_H_